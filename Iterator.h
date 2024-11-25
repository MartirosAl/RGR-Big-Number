#pragma once
class Iterator
{
   short* arr;
   size_t index;

public:

   Iterator(short* begin, size_t index_ = 0) : arr(begin), index(index_) {}
   short& operator*()
   {
      if (!arr)
         throw "There is no pointer";
      return arr[index];
   }

   short* operator->()
   {
      if (!arr)
         throw "There is no pointer";
      return arr;
   }

   Iterator& operator++()
   {
      if (!arr)
         throw "There is no pointer";
      index++;
      return *this;
   }

   bool operator==(const Iterator& other_) const
   {
      return arr[index] == other_.arr[index];
   }

   bool operator!=(const Iterator& other_) const
   {
      return arr[index] != other_.arr[index];
   }
};



