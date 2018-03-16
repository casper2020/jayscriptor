#include "casper/dm_data_source.h"
#include <iostream>

casper::MyDataSource::MyDataSource (){
    data_source_row_index_ = 0;
    data_source_row_count_ = 0;
}

casper::MyDataSource::~MyDataSource (){
    /* empty */
}

void casper::MyDataSource::AppendDataRow (const casper::SymbolTable& a_row){
    casper::SymbolTable new_line;
    for ( auto symb : a_row ) {
        new_line[symb.first] = symb.second;
    }
    lines_.push_back(new_line);
    data_source_row_count_++;
}

void casper::MyDataSource::SetParameter (const char* a_name, const Term& a_value){
    scalars_[a_name] = a_value;
}

void casper::MyDataSource::SetField (const char* a_name, const Term& a_value){


    if ( lines_.size() == 0 || static_cast<size_t>(data_source_row_index_) >= lines_.size() ) {
        throw OSAL_EXCEPTION_NA("Data source row index out of limits!");
    }
    auto it = lines_[data_source_row_index_].find(a_name);
    if ( lines_[data_source_row_index_].end() == it ) {
        throw OSAL_EXCEPTION_NA("Field not found for the current data source row index!");
    }

    it->second = a_value;
}

void casper::MyDataSource::AddEmptyRow  (){
    casper::SymbolTable tmp_st;
    lines_.push_back(tmp_st);
    data_source_row_count_++;
}

const casper::Term* casper::MyDataSource::GetParameter  (const char* a_param_name){
    auto it = scalars_.find(a_param_name);
    if ( scalars_.end() != it ) {
        return &it->second;
    }
    return nullptr;
}

const casper::Term* casper::MyDataSource::GetField (const char* a_field_name){
    if ( lines_.size() == 0 || static_cast<size_t>(data_source_row_index_) >= lines_.size() ) {
        return nullptr;
    }
    auto it = lines_[data_source_row_index_].find(a_field_name);
    if ( lines_[data_source_row_index_].end() != it ) {
        return &it->second;
    }
    return nullptr;
}

void casper::MyDataSource::Rewind (){
    data_source_row_index_ = 0;
}
