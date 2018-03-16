#include "casper/abstract_data_source.h"

// Tens que ter uma implementaçao de data data_source_
namespace casper {
  class MyDataSource : public AbstractDataSource
  {
  protected: // data
      SymbolTable              scalars_;
      std::vector<SymbolTable> lines_;

  public:
      virtual void        SetParameter  (const char* a_name, const Term& a_value);
      virtual void        SetField      (const char* a_name, const Term& a_value);
      virtual void        AddEmptyRow   ();
      virtual const Term* GetParameter  (const char* a_param_name);
      virtual const Term* GetField      (const char* a_field_name);
      virtual void        AppendDataRow (const casper::SymbolTable& a_row);
      virtual void        Rewind        ();

               MyDataSource ();
      virtual ~MyDataSource ();
  };
}
