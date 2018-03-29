//
// Created by everettjf on 2017/7/23.
//

#ifndef MOEX_VIEWNODE_H
#define MOEX_VIEWNODE_H

#include "../moex.h"
#include <initializer_list>
#include <vector>

MOEX_NAMESPACE_BEGIN

//////////////////////////////// View Data ///////////////////////////////////////
enum class ViewDataMode{
    Binary,
    Table,
};
class ViewData{
protected:
    ViewDataMode mode_;
    std::string title_;
public:
    ViewDataMode mode()const{return mode_;}
    const std::string & title()const{return title_;}
    void set_title(const std::string & title){title_ = title;}
};
using ViewDataPtr = std::shared_ptr<ViewData>;

///////////////////////////////// View Data - Binary ////////////////////////////
class BinaryViewData: public ViewData{
public:
    char * offset = nullptr;
    uint64_t size = 0;
    uint64_t start_value = 0;

    BinaryViewData(){
        mode_ = ViewDataMode::Binary;
        title_ = "Binary";
    }
    bool IsEmpty()const{return offset == nullptr;}
};
using BinaryViewDataPtr = std::shared_ptr<BinaryViewData>;
inline BinaryViewDataPtr CreateBinaryViewDataPtr(){return std::make_shared<BinaryViewData>();}

///////////////////////////////// View Data - Table ////////////////////////////
class TableViewItem{
public:
    std::string data;
};
using TableViewItemPtr = std::shared_ptr<TableViewItem>;

class TableViewRow{
public:
    std::vector<TableViewItemPtr> items;

    void SetValues(const std::initializer_list<std::string> & vals);
};
using TableViewRowPtr = std::shared_ptr<TableViewRow>;

class TableViewHeaderItem{
public:
    std::string data;
};
using TableViewHeaderItemPtr = std::shared_ptr<TableViewHeaderItem>;

class TableViewData : public ViewData{
public:
    std::vector<TableViewHeaderItemPtr> headers;
    std::vector<TableViewRowPtr> rows;
    std::vector<uint32_t> widths;

    TableViewData();

    bool IsEmpty()const{return rows.empty();}

    void SetHeaders(const std::initializer_list<std::string> & vals);
    void SetWidths(const std::initializer_list<uint32_t> & vals);
    void AddRow(const std::initializer_list<std::string> & vals);

    template <typename T>
    void AddRow(uint64_t addr,T data,const std::string & desc,const std::string & val);

    void AddRow(uint64_t addr,const std::string & data,const std::string & desc,const std::string & val);
    void AddRow(uint64_t addr,void* data,size_t size,const std::string & desc,const std::string & val);
    void AddRow(const std::string & addr,const std::string & data,const std::string & desc,const std::string & val);

    void AddSeparator();
};
using TableViewDataPtr = std::shared_ptr<TableViewData>;
inline TableViewDataPtr CreateTableViewDataPtr(){return std::make_shared<TableViewData>();}
inline TableViewDataPtr CreateTableViewDataPtr(const std::string & title){auto x=std::make_shared<TableViewData>();x->set_title(title);return x;}


template<typename T>
void TableViewData::AddRow(uint64_t addr, T data, const std::string &desc, const std::string &val)
{
    AddRow({util::AsAddress(addr),util::AsHexData(data),desc,val});
}


///////////////////////////////// View Node Base Class ///////////////////////////////


class ViewNode {
protected:
    std::vector<ViewDataPtr> view_datas_;
protected:
    void AddViewData(ViewDataPtr val){
        view_datas_.push_back(val);
    }
public:
    virtual ~ViewNode(){

    }
    std::vector<ViewDataPtr> & GetViewDatas(){
        if(view_datas_.empty()){
            InitViewDatas();
        }
        return view_datas_;
    }

public:
    virtual std::string GetDisplayName(){
        return "unknown";
    }
    virtual void ForEachChild(std::function<void(ViewNode*)>){

    }
    virtual void InitViewDatas(){

    }
};


MOEX_NAMESPACE_END

#endif //MOEX_VIEWNODE_H
