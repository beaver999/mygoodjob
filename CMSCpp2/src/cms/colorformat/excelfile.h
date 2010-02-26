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
	    const Mode mode;
	     std::string fileName;
	     std::string tableName;
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
	    //ExcelFileDB(string_ptr fileName, const Mode mode);
	     ExcelFileDB(const std::string & fileName, const Mode mode);
	    ~ExcelFileDB();
	    /*void createTable(string_ptr tableName,
	       string_vector_ptr fieldNames); */
	    void createTable(const std::string & tableName,
			     string_vector_ptr fieldNames);
	    void createTable(const std::string & tableName,
			     string_vector_ptr fieldNames,
			     string_vector_ptr fieldTypes);

	    //void setTableName(string_ptr tablename);
	    void setTableName(const std::string & tableName);
	    void insert(string_vector_ptr fieldNames,
			string_vector_ptr values);
	    void insert(string_vector_ptr fieldNames,
			string_vector_ptr values, bool text);



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


	    void setKeyField(const std::string & keyField);
	  private:
	    void close();
	};

	class DGCodeFile {
	  private:
	    bptr < ExcelFileDB > db;
	    const Mode mode;
	    void init();
	    void initDefaultData(string_vector_ptr fieldNames,
				 const std::string & tableName,
				 bool reverse);
	    const int n;
	    static string_vector_ptr getFieldNames(const std::string *
						   fieldNames, int n);
	  public:
	    static const std::string GammaHeader[4];
	    static const std::string RawHeader[13];
	    static const std::string PropertiesHeader[2];
	    static const std::string & GammaTable;
	    static const std::string & RawData;
	    static const std::string & Properties;
	     DGCodeFile(const std::string & filename, int n);
	     DGCodeFile(const std::string & filename, int n,
			const Mode mode);
	    void setProperty(const std::string & key,
			     const std::string & value);
	};
    };
};
#endif

