#include "jxmlparser.h"

#include <string>
#include <iostream>
#include <iostream>
#include <sstream>

using namespace jcommon;

struct luaxml_t {
	std::string id;
	int field; // 0: text, 1: attribute
	int index;
};

std::string xml;

/*
 * \brief Request parameters from a xml document.
 *
 * text value:
 * 		x.y.z
 * 		x.y[i].z
 * 		x.[i]
 * attribute value:
 * 		x.y[i].z:[j]
 * 		x.y[i].z:w
 */
std::string xmlmap(std::string id)
{
	std::vector<luaxml_t> tags;
	std::string tag,
		index;
	int i = 0,
		j,
		state = 255;
	char c;

	while ((c = id[i++]) != '\0') {
		if (state == 255) {
			tag = "";
			index = "";
			if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
				tag = c;
				state = 0;
			}
		} else if (state == 0) {
			if (c == '.') {
				struct luaxml_t t;

				t.id = tag;
				t.index = 0;
				t.field = 0;

				tags.push_back(t);

				// printf(":: state::[%d], tag::[%s] index::[0]\n", state, tag.c_str());
				tag = "";
			} else if (c == ':') {
				struct luaxml_t t;

				t.id = tag;
				t.index = 0;
				t.field = 0;

				tags.push_back(t);

				// printf(":: state::[%d], tag::[%s] index::[0]\n", state, tag.c_str());
				tag = "";
				state = 2;
			} else if (c == '[') {
				state = 1;
			} else {
				tag = tag + c;
			}
		} else if (state == 1) {
			if (c == ']') {
				struct luaxml_t t;

				t.id = tag;
				t.index = atoi(index.c_str());
				t.field = 0;

				tags.push_back(t);

				// printf(":: state::[%d], tag::[%s] index::[%s]\n", state, tag.c_str(), index.c_str());
				state = 255;
			} else if (c >= '0' && c <= '9') {
				index = index + c;
			}
		} else if (state == 2) {
			if (c == '[') {
				state = 3;
			} else {
				tag = tag + c;
			}
		} else if (state == 3) {
			if (c == ']') {
				struct luaxml_t t;

				t.id = "";
				t.index = atoi(index.c_str());;
				t.field = 1;

				tags.push_back(t);

				// printf(":: state::[%d], index::[%s]\n", state, index.c_str());
				break;
			} else if (c >= '0' && c <= '9') {
				index = index + c;
			}
		}
	}

	if (state == 0) {
		struct luaxml_t t;

		t.id = tag;
		t.index = 0;
		t.field = 0;

		tags.push_back(t);

		// printf(":: state::[%d], tag::[%s] index::[0]\n", state, tag.c_str());
	} else if (state == 2) {
		struct luaxml_t t;

		t.id = tag;
		t.index = 0;
		t.field = 1;

		tags.push_back(t);

		// printf(":: state::[%d], tag::[%s] index::[0]\n", state, tag.c_str());
	}

	printf(":: %s\n", id.c_str());
	for (std::vector<struct luaxml_t>::iterator i=tags.begin(); i!=tags.end(); i++) {
		// printf("::tag:: %s, index:: %d\n", (*i).id.c_str(), (*i).index);
	}

	// xml parser
	XmlDocument doc;

	doc.Parse(xml.c_str());

	if (doc.Error()) {
		return "";
	}

	XmlElement *psg;

	// root = doc.RootElement()->FirstChildElement("body");
	
	psg = doc.RootElement();

	if (psg == NULL) {
		return "";
	}

	i = 0;

	while (i < tags.size()) {
		struct luaxml_t t = tags[i];

		if (psg == NULL) {
			return "";
		}

		if (t.field == 0) {
			j = 0;

			while (j < t.index) {
				// TODO:: sair daqui
				if (t.id == "" || strcmp(psg->Value(), t.id.c_str()) == 0) {
					j++;
				}

				psg = psg->NextSiblingElement();

				if (psg == NULL) {
					return "";
				}
			}
			
			if (j != t.index) {
				return "";
			}

			i++;

			if (i == tags.size()) {
				return psg->GetText();
			} else {
				if (tags[i].field == 0) {
					psg = psg->FirstChildElement();
				}
			}
		} else if (t.field == 1) {
			if (t.id != "") {
				if (psg->Attribute(t.id.c_str()) != NULL) {
					return psg->Attribute(t.id.c_str());
				} else {
					return "";
				}
			} else {
				jcommon::XmlAttribute *attr = psg->FirstAttribute();

				for (j=0; j<t.index; j++) {
					attr = attr->Next();

					if (attr == NULL) {
						return "";
					}
				}

				if (j != t.index) {
					return "";
				}

				return attr->Value();
			}
		} else {
			return "";
		}
	}

	return "";
}

int main()
{
	xml = ""
		"<html>"
		"<body>"
		"<p>p1</p>"
		"<p>p2</p>"
		"<p>p3</p>"
		"<p><font color=#00ff00 size=12 name=arial>p4</font></p>"
		"<font color=#001122>ifont</font>"
		"</body>"
		"</html>";

	std::string s;

	s = xmlmap("html.body.p");
	printf("Return:: [%s]\n", s.c_str());
	s = xmlmap("html.body.p[2]");
	printf("Return:: [%s]\n", s.c_str());
	s = xmlmap("html.body.p[3].font");
	printf("Return:: [%s]\n", s.c_str());
	s = xmlmap("html.body.[1]");
	printf("Return:: [%s]\n", s.c_str());
	s = xmlmap("html.body.p[3].font:size");
	printf("Return:: [%s]\n", s.c_str());
	s = xmlmap("html.body.p[3].font:[2]");
	printf("Return:: [%s]\n", s.c_str());
	
	return 0;
}

