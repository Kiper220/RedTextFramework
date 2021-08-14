//
// Created by kiper220 on 23.07.2021.
//
#include <RTD/Types/SharedPointer.h>
#include <RTD/Types/Iterator.h>

#ifndef REDTEXTAPPLICATION_LIST_H
#define REDTEXTAPPLICATION_LIST_H

namespace RTF{
    namespace Container{
        template<typename T>
        class SharedList{
        public:

            class ListType{
            public:
                class Item{
                public:
                    Item(T& variable, Types::SharedPointer<Item> backItem = (Item*)nullptr, Types::SharedPointer<Item> frontItem = (Item*)nullptr): itemValue(variable), backItem(backItem), frontItem(frontItem) {}
                    Item(const T& variable, Types::SharedPointer<Item> backItem = (Item*)nullptr, Types::SharedPointer<Item> frontItem = (Item*)nullptr): itemValue(variable), backItem(backItem), frontItem(frontItem) {}
                    Item(T&& variable, Types::SharedPointer<Item> backItem = (Item*)nullptr, Types::SharedPointer<Item> frontItem = (Item*)nullptr): itemValue(variable), backItem(backItem), frontItem(frontItem) {}

                    Item& SetValue(T& variable){
                        this->itemValue = variable;
                        return *this;
                    }
                    Item& SetValue(const T& variable){
                        this->itemValue = variable;
                        return *this;
                    }
                    Item& SetValue(T&& variable){
                        this->itemValue = variable;
                        return *this;
                    }
                    Item& SetBackItem(Types::SharedPointer<Item> &backItem){
                        this->backItem = backItem;
                        return *this;
                    }
                    Item& SetFrontItem(Types::SharedPointer<Item> &frontItem){
                        this->frontItem = frontItem;
                        return *this;
                    }
                    Types::SharedPointer<Item>& GetBackItem(){
                        return this->backItem;
                    }
                    Types::SharedPointer<Item>& GetFrontItem(){
                        return this->frontItem;
                    }
                    Item& DestructBackItem(){
                        this->backItem.DestructThis();
                        return *this;
                    }
                    Item& DestructFrontItem(){
                        this->frontItem.DestructThis();
                        return *this;
                    }
                    T& GetValue(){
                        return this->itemValue;
                    }


                private:
                    T itemValue;
                    Types::SharedPointer<Item> backItem;
                    Types::SharedPointer<Item> frontItem;
                };

            public:
                class Iterator: public Types::Iterator<T>{
                public:
                    Iterator() = default;
                    Iterator(const Iterator& iterator){
                        this->thisItem = iterator.thisItem;
                    }
                    Iterator(Types::SharedPointer<Item> itemPointer){
                        this->thisItem = itemPointer;
                    }

                    Types::Iterator<T>& StepBack() override{
                        this->thisItem = (*this->thisItem).GetBackItem();
                        return *this;
                    }
                    Types::Iterator<T>& StepForward() override{
                        this->thisItem = (*this->thisItem).GetFrontItem();
                        return *this;
                    }

                    Types::Iterator<T>& StepBackBy(uint64_t steps) override{
                        if(steps == 0) return *this;

                        while(this->thisItem != nullptr && steps-- != 0)
                            this->thisItem = (*this->thisItem).GetBackItem();

                        return *this;
                    }
                    Types::Iterator<T>& StepForwardBy(uint64_t steps) override{
                        if(steps == 0) return *this;

                        while(this->thisItem != nullptr && steps-- != 0)
                            this->thisItem = (*this->thisItem).GetFrontItem();

                        return *this;
                    }

                    T& GetValue() override{
                        return (*this->thisItem).GetValue();
                        return *this;
                    }
                    Types::Iterator<T>& SetValue(T value) override{
                        (*this->thisItem).SetValue(value);
                        return *this;
                    }
                    Types::Iterator<T>& SetValue(T& value) override{
                        (*this->thisItem).SetValue(value);
                        return *this;
                    }
                    Types::Iterator<T>& SetValue(const T& value) override{
                        (*this->thisItem).SetValue(value);
                        return *this;
                    }

                    Iterator operator++(int){
                        Iterator iterator = *this;
                        this->StepForward();

                        return iterator;
                    }
                    Iterator& operator++(){
                        this->StepForward();
                        return *this;
                    }

                    Iterator operator--(int){
                        Iterator iterator = *this;
                        this->StepBack();

                        return iterator;
                    }
                    Iterator& operator--(){
                        this->StepBack();
                        return *this;
                    }

                    bool operator==(const Iterator& iterator) const{
                        return this->thisItem == iterator.thisItem;
                    }
                    bool operator!=(const Iterator& iterator) const{
                        return this->thisItem != iterator.thisItem;
                    }

                    Iterator& operator=(const Iterator& iterator){
                        this->thisItem = iterator.thisItem;
                        return *this;
                    }
                    Iterator& operator=(Types::SharedPointer<Item> itemPointer){
                        this->thisItem = itemPointer;
                        return *this;
                    }
                    Iterator& operator=(T value){
                        (*this->thisItem).SetValue(value);
                        return *this;
                    }
                    Iterator& operator=(T& value){
                        (*this->thisItem).SetValue(value);
                        return *this;
                    }
                    Iterator& operator=(const T& value){
                        (*this->thisItem).SetValue(value);
                        return *this;
                    }
                    T& operator*(){
                        return (*this->thisItem).GetValue();
                    }

                    operator T&(){
                        return (*this->thisItem).GetValue();
                    }

                    ~Iterator() override = default;

                private:
                    Types::SharedPointer<Item> thisItem;
                };

            public:

                ListType() = default;

                ListType& PushBack(const T& variable){
                    if(backOfList.IsEmpty()) {
                        frontOfList = new Item(std::move(variable));
                        backOfList = frontOfList;

                        this->lengthOfList++;
                        return *this;
                    }
                    Types::SharedPointer<Item> pointerItem;
                    pointerItem = new Item(std::move(variable), frontOfList);

                    (*frontOfList).SetFrontItem(pointerItem);
                    frontOfList = std::move(pointerItem);

                    this->lengthOfList++;
                    return *this;
                }
                ListType& PushBack(T&& variable){
                    if(backOfList.IsEmpty()) {
                        frontOfList = new Item(variable);
                        backOfList = frontOfList;

                        this->lengthOfList++;
                        return *this;
                    }
                    Types::SharedPointer<Item> pointerItem(new Item(variable, frontOfList));

                    (*frontOfList).SetFrontItem(pointerItem);
                    frontOfList = pointerItem;

                    this->lengthOfList++;
                    return *this;
                }

                T& GetItem(uint64_t i){
                    Types::SharedPointer<Item> retVal = backOfList;

                    for(uint64_t j = 0; j < i && retVal != frontOfList; j++)
                        retVal = (*retVal).GetFrontItem();

                    return (*retVal).GetValue();
                }

                void DestructThis(){
                    Types::SharedPointer<Item> pointer = backOfList, tmp;

                    while(pointer != frontOfList){
                        tmp = (*pointer).GetFrontItem();

                        (*pointer).DestructBackItem();
                        (*pointer).DestructFrontItem();

                        pointer = tmp;
                    }
                    (*pointer).DestructBackItem();

                    backOfList.DestructThis();
                    frontOfList.DestructThis();
                }
                Iterator begin(){
                    return this->backOfList;
                }
                Iterator end(){
                    return Types::SharedPointer<Item>();
                }

                ~ListType() {
                    this->DestructThis();
                }
            private:
                Types::SharedPointer<Item> backOfList;
                Types::SharedPointer<Item> frontOfList;

                uint64_t lengthOfList = 0;

            };

        public:


        private:
            Types::SharedPointer<T> pointerOfList;

        };
    }
}

#endif //REDTEXTAPPLICATION_LIST_H
