#ifndef EXCELFILEH
#define EXCELFILEH
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���
#include <ADODB.hpp>
#include <DB.hpp>
//�����ؤ��Y���
#include <java/lang.h>

namespace cms {
    namespace colorformat {
	enum Mode {
	    Create, Update, ReadOnly
	};


	class ExcelFile {
	};
	class ExcelFileDB {
	  private:
	    //TADOConnection * ADOConnection1;
	    bptr < TADOConnection > connection;
	    Mode mode;
	    string_ptr fileName;
	    string_ptr tableName;
	     bptr < WideString > toWideString(const std::string & sql);
	    string_vector_ptr fieldNames;
	     std::string keyField;
	    bool tableChanged;
	  public:
	     string_vector_ptr getFieldNames(string_ptr tableName);
	  protected:
	     bool isAlterable();
	    void execute(const std::string & sql);
	    void update0(const std::string & keyField,
			 const int &keyValue,
			 string_vector_ptr fieldNames,
			 string_vector_ptr values, bool textValues);
	  public:
	     ExcelFileDB(string_ptr fileName, Mode mode);
	    ~ExcelFileDB();
	    void createTable(string_ptr tableName,
			     string_vector_ptr fieldNames);
	    void setTableName(string_ptr tablename);
	    void setTableName(const std::string & tablename);
	    void insert(string_vector_ptr fieldNames,
			string_vector_ptr values);


	    void update(const std::string & keyField,
			const int &keyValue,
			string_vector_ptr fieldNames,
			string_vector_ptr values);
	    void update(const std::string & keyField,
			const int &keyValue,
			const std::string & fieldName,
			const std::string & value);
	    void update(const std::string & keyField,
			const int &keyValue,
			const std::string & fieldName, const int &value);

	    //void update(const int &keyValue, string_vector_ptr values);
	    string_vector_ptr select(const std::string & keyField,
				     const int &keyValue);
	    string_vector_ptr select(const int &keyValue);

	    void close();
	    void setKeyField(const std::string & keyField);
	};
    };
};
#endif

