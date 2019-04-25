//
// Created by Admin on 24.04.2019.
//

#ifndef VIRTUALFUNCTIONS_VIRTUALITY_H

//////////////////////////
/// MACROS DEFINITIONS ///
//////////////////////////

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <bits/stdc++.h>
#include <typeinfo>
#include <exception>

std::map<std::string, std::function<void()>> *link = nullptr;
std::map<std::string, std::set<std::string>> _func_presented;

#define VIRTUAL_CLASS(cls_name) \
    namespace nsp_##cls_name{ \
        std::map<std::string, std::function<void()>> _v_table; \
    } \
    struct cls_name { \
        std::map<std::string, std::function<void()>>* _v_table_ptr{&nsp_##cls_name::_v_table};

#define END_CLASS(cls_name) \
    };

#define DECLARE_METHOD(cls_name, func_name) \
    namespace nsp_##cls_name{ \
        void _func_##cls_name##_##func_name() {

#define END_METHOD(cls_name, func_name) \
        } \
        struct _struct_##cls_name##_##func_name { \
            _struct_##cls_name##_##func_name () { \
                cls_name e; \
                std::string right_cls_name = typeid(&e).name() ; \
                auto it = _func_presented.find(right_cls_name); \
                if(it == _func_presented.end()) { \
                    std::set<std::string> s; \
                    _func_presented.emplace(std::make_pair(right_cls_name, s)) ; \
                } \
                it = _func_presented.find(right_cls_name) ; \
                it->second.emplace(#func_name); \
                _v_table.erase(#func_name); \
                _v_table.emplace(std::make_pair( \
                        #func_name, \
                        _func_##cls_name##_##func_name)); \
            } \
        } _instance_##cls_name##_##func_name; \
    }

#define VIRTUAL_INVOKE(inst_ptr, func_name) \
    { \
        auto it = _func_presented.find(typeid(inst_ptr).name()); \
        if(it->second.find(#func_name) != it->second.end()) { \
            link = reinterpret_cast<std::map<std::string, std::function<void()>>*>((unsigned int*)(*((unsigned int*)inst_ptr))); \
            link->find(#func_name)->second(); \
        } else { \
            throw std::runtime_error("function not presented"); \
        } \
    }


#define VIRTUAL_CLASS_DERIVED(cls_name, bs_name) \
    namespace nsp_##cls_name{ \
        std::map<std::string, std::function<void()>> _v_table(nsp_##bs_name::_v_table); \
    } \
    struct cls_name { \
        std::map<std::string, std::function<void()>>* _v_table_ptr{&nsp_##cls_name::_v_table};

#define END_CLASS_DERIVED(cls_name, bs_name) \
    };


#define VIRTUALFUNCTIONS_VIRTUALITY_H

#endif //VIRTUALFUNCTIONS_VIRTUALITY_H
