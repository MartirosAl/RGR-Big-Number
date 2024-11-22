#include "BigNumber.h"

BigNumber::BigNumber(size_t new_cap_)
{
   number = new Nial[new_cap_];
   capacity = new_cap_;
   size = 0;
}

BigNumber::BigNumber(Nial* number_, size_t size_)
{
   size_t i = 1;
   for (i = 1; 100 * i < size_; i++);
   capacity = 100 * i;
   number = new Nial[capacity];
   size = size_;

   for (i = 0; i < size; i++)
      number[i] = number_[i];
}

BigNumber::~BigNumber()
{
   if (number)
      delete[] number;
   number = nullptr;
   size = 0;
   capacity = 0;
}

BigNumber::BigNumber(const BigNumber& other_)
{
   this->Clear();
   size = other_.size;
   capacity = other_.capacity;
   number = new Nial[other_.capacity];
   
   for (size_t i = 0; i < other_.size; i++)
      number[i] = other_[i];

}

size_t BigNumber::Get_Capacity()
{
   return capacity;
}

size_t BigNumber::Get_Size()
{
   return size;
}

Nial& BigNumber::operator[](size_t index_) const
{
   if (index_ > capacity)
      throw "Out of range";
   return number[index_];
}

Nial& BigNumber::operator[](size_t index_) 
{
   if (index_ > capacity)
      throw "Out of range";
   return number[index_];
}

BigNumber& BigNumber::operator=(const BigNumber& other_)
{
   if (other_.size >= capacity)
   {
      this->Clear();
      capacity = other_.capacity;
      number = new Nial[other_.capacity];
   }

   size = other_.size;
   for (size_t i = 0; i < size; i++)
      number[i] = other_[i];

   return *this;
}

BigNumber BigNumber::operator+(const BigNumber& other_) const
{
   BigNumber tempBN(capacity < other_.capacity ? other_ : *this);
   //¬ыбираем где больше места, чтобы меньше трогать Expansion

   Nial adddigit = 0;
   
   for (size_t i = 0; i < size || i < other_.size; i++)
   {
      Nial temp = number[i] + other_[i] + adddigit;
      tempBN[i] = temp % 10;
      adddigit = temp / 10;
   }

   if (adddigit && size == other_.size)
   {
      if (size == capacity)
         tempBN.Expansion(size + 1);
      tempBN[size] = adddigit;
   }
   
   //—мотрим что больше и дополн€ем до него
   for (size_t i = (size < other_.size ? size : other_.size) + 1; i < (size < other_.size ? other_.size : size); i++)
   {
      tempBN[i] = (size < other_.size ? number[i] : other_[i]);
   }

   tempBN.size += size - other_.size ? size - other_.size : other_.size - size;

   return tempBN;
}

BigNumber& BigNumber::operator+=(const BigNumber& other_)
{
   if (capacity < other_.size)
      Expansion(other_.capacity);

   Nial adddigit = 0;
   // ≈сли другое число больше нашего, тогда мы уже сделали расширение или нам достаточно места
   // ѕросто складываем одну цифру с другой и кладем по местам 
   if (size < other_.size)
   {
      for (size_t i = 0; i < size; i++)
      {
         Nial temp = number[i] + other_[i] + adddigit;
         number[i] = temp % 10;
         adddigit = temp / 10;
      }
      number[size] = adddigit + other_[size];

      for (size_t i = size + 1; i < other_.size; i++)
         number[i] = other_[i];

      size = other_.size;
      return *this;
   }

   for (size_t i = 0; i < other_.size; i++)
   {
      Nial temp = number[i] + other_[i] + adddigit;
      number[i] = temp % 10;
      adddigit = temp / 10;
   }

   // ≈сли мы пропустили size < other_.size, то значит размер у нас либо такой же либо больше,
   // а следовательно и выделенна€ пам€ть тоже либо больше либо равна                          
   if (adddigit && size == other_.size)
   {
      if (size == capacity)
         Expansion();
      number[size] = adddigit;
      size++;
   }

   return *this;
      
}

void BigNumber::Clear()
{
   delete[] number;
   number = nullptr;
   size = 0;
   capacity = 0;
}


//void BigNumber::Number_Shift(int index_)
//{
//   //отдельно случай, когда значений нет
//   if (size == 0)
//   {
//      if (capacity < index_)
//         Expansion();
//      for (size_t i = 0; i < index_; i++)
//         number[i] = 0;
//      size += index_;
//      printf("%d.\n", number[0]);
//      return;
//   }
//
//   if (index_ > 0)
//   {
//      if (size + index_ >= capacity)
//         Expansion();
//      for (size_t i = size - 1; i > 0; i--)
//      {
//         printf("%d %d %d\n", number[i + index_], number[i], i);
//         number[i + index_] = number[i];
//         number[i] = 0;
//         printf("%d %d %d %d\n", size,  i + index_, number[i + index_], number[i]);
//      }
//      number[index_] = number[0];
//      number[0] = 0;
//
//      for (size_t i = 0; i < size; i++)
//         printf("%d ", number[i]);
//      printf(".\n");
//
//   }
//   else if (index_ < 0)
//      for (size_t i = size - 1; i >= -index_; i--)
//         number[i + index_] = number[i];
//
//   size += index_;
//}


void BigNumber::Number_Shift(size_t index_)
{
   if (index_ == 0)
      return;
   while (capacity < size + index_)
      Expansion();

   //size_t i = 0 - 1 это очень много
   if (size == 0)
   {
      number[0] = 0;
      size++;
      return;
   }
   
   //»дем от последнего числа
   for (size_t i = size - 1; i > 0; i--)
   {
      number[i + index_] = number[i];
   }
   number[index_] = number[0];
   for (size_t i = 0; i < index_; i++)
      number[i] = 0;
   size += index_;
}

void BigNumber::Expansion()
{
   Nial* temp_arr = new Nial[size];

   for (size_t i = 0; i < size; i++)
      temp_arr[i] = number[i];

   if (capacity > 0)
      delete[] number;
   
   number = new Nial[capacity + 100];
   capacity += 100;

   for (size_t i = 0; i < size; i++)
      number[i] = temp_arr[i];
   
}

void BigNumber::Expansion(size_t new_cap_)
{
   if (new_cap_ <= capacity)
      return;

   Nial* temp_arr = new Nial[size];

   for (size_t i = 0; i < size; i++)
      temp_arr[i] = number[i];

   
   number = new Nial[new_cap_];
   capacity = new_cap_;

   for (size_t i = 0; i < size; i++)
      number[i] = temp_arr[i];
}

ostream& operator<<(ostream& stream, const BigNumber& object_)
{
   if (object_.size > 0)
   {
      for (size_t i = object_.size - 1; i > 0; i--)
      {
         stream << object_[i];
      }
      // ќтдельно, т.к. если i >= 0, то тип size_t будет замен€ть отрицательные числа на 0 
      // и получитс€, что 0 - 1 = 0 -> продолжаем цикл
      stream << object_[0];
   }

   return stream;
}

istream& operator>>(istream& stream, BigNumber& object_)
{
   Nial* reinsurance = new Nial[object_.size];
   for (size_t i = 0; i < object_.size; i++)
      reinsurance[i] = object_[i];
   size_t reinsurance_size = object_.size;
   size_t reinsurance_capacity = object_.capacity;

   if (object_.size != 0)
      object_.Clear();

   object_.number = new Nial[100];

   char digit[2];

   while (stream.peek() != '\n')
   {
      stream.get(digit, 2);
      if (digit[0] < '0' || digit[0] > '9')
      {
         stream.setstate(ios::badbit);

         delete[] object_.number;
         object_.number = new Nial[reinsurance_capacity];
         for (size_t i = 0; i < reinsurance_size; i++)
            object_[i] = reinsurance[i];
         
         object_.size = reinsurance_size;
         object_.capacity = reinsurance_capacity;
         return stream;
      }

      object_.Number_Shift(1);

      //test
      //for (size_t i = object_.size - 1; i > 0; i--)
      //   cout << object_[i];
      //cout << object_[0] << endl;

      object_[0] = digit[0] - '0';
   }
   stream.ignore();//»гнорируем \n

   return stream;
}


