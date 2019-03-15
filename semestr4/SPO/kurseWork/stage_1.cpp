/// ===================================================================================
Всего заданий 8

// № 1, 2
task 1 2 : just reading
// ---------------------------------------------------------------------------------

// № 3    
task : Напишите программу, проверяющую число на четность.
	
Check number, it's even or not
num : is_even dup 2 / 2 * = . cr ;
// -----------------------------------------------------------------------

// № 4   
task : Напишите программу, проверяющую число на простоту.

Check is (a mod b == 0) true or false. Time complexity O(1)
a b : divideble dup rot dup rot / rot * = ;

Simple counting number of dividers of n. Time complexity O(N)
n : count_dividers 0 swap dup 1 + 1 for dup r@ divideble rot + swap endfor swap ;

Simple ( very simple ) checking n - is prime or not. Time complexity O(N)
n : is_prime count_dividers 2 = if . ."  - prime" else . ."  - not prime" then cr ; 
/// ---------------------------------------------------------------------

// № 5  
task : Напишите программу так, чтобы она выделяла с помощью allot ячейку в памяти, записывала
туда результат и возвращала её адрес. Вам могут потребоваться слова @, !, @c, !c. Слово allot
принимает количество байт для выделения в глобальной области данных.

I can't truli imagine what task mean, so I did two type of allot. I hope it's enought good.

// allot version 1. .............................................................
Напишите программу так, чтобы она выделяла с помощью allot ячейку в 
памяти, записывала туда результат и возвращала её адрес.

Check is (a mod b == 0) true or false. Time complexity O(1)
a b : divideble dup rot dup rot / rot * = ;

Simple counting number of dividers of n. Time complexity O(N)
n : count_dividers 0 swap dup 1 + 1 for dup r@ divideble rot + swap endfor swap ;

Simple ( very simple ) checking n - is prime or not. Time complexity O(N)
n : is_prime count_dividers 2 = if 1 else 0 then cr ;

n : allot is_prime dp dup rot swap ! ;


// allot version 2 ...........................................................................
Слово allot принимает количество байт для выделения в глобальной области данных.

Check is (a mod b == 0) true or false. Time complexity O(1)
a b : divideble dup rot dup rot / rot * = ;

Simple counting number of dividers of n. Time complexity O(N)
n : count_dividers 0 swap dup 1 + 1 for dup r@ divideble rot + swap endfor swap ;

Simple ( very simple ) checking n - is prime or not. Time complexity O(N)
n : is_prime count_dividers 2 = if 1 else 0 then cr ;

Ad to x to each memory container from dp to dp + kol
x kol : add_to_memory 0 for dup r@ dp + c! endfor dp ;

Put to all memory containers from dp to dp_kol - the result of checking n is prime or not.
kol n : allot is_prime rot add_to_memory ;

kol : asave 0 for r@ dup dp + c! endfor ;
kol : aread 0 for r@ dp + c@ . endfor ;

/// ------------------------------------------------------------------------------

// № 6
reading tutorial
/// ---------------------------------------------------------------------------

// № 7 
task : Прочитайте про слова c@, c!. Напишите слово, которое принимает указатели на две строки и
возвращает их конкатенацию. Память под строку-результат вы можете выделить с помощью
слова heap−alloc, которое принимает количество байт для выделения и
Протестируйте полученное слово. Нет ли утечки памяти?
	
@ (addr - значение) Получить значение из памяти.
! (val addr -) Сохранить значение по адресу.
с! (char addr -) Сохранять один байт по адресу.
c@ (addr - char) Чтение одного байта, начиная с адреса.

Get string addres and count it's length
adr 
: str_len 
    dup 0 
    repeat 
      swap dup c@ swap 
      1 + rot 
      1 + rot 
      0 = 
    until 
    1 - 
    swap ." str end " . cr 
    dup ." str len = " . cr ;

Zapisat stroky iz adr1 v adr2 
adr1 adr2 
: copy_string 
    swap 
    repeat 
      dup rot dup rot 
      c@ swap c! dup c@ 
      rot 1 + rot 1 + 
      swap rot 
      0 = 
    until 
    ." str end ". 
    cr 1 - ;


adr1 adr2
: sum_string 
	str_len     ( count len1 of first string ) 
	rot
	str_len     ( count len2 of second string )
	rot + heap-alloc  ( make string with size len1+len2 in heap )
	dup ." result addres is " . cr
	dup >r rot rot r> ( for saving result addres )
	copy_string     ( copy first string to ans )
	copy_string     ( copy second string to ans )
	." str end " . cr
	;
///-------------------------------------------------------------------------------------
  
// № 8
	Задание по вариантам 
  I can't calculate my variante, so I did tasks for all variants.
  
var : 1
  Task : Напишите слово, которое проведёт проверку числа на примарность.
         Примарным называется число, которое представляется в виде произведения простых без повторов. 
	 Например, число 4 не примарное, т.к. 4 = 2 2 ; 20 – не примарное число, т.к. 20 = 2 2 · 5 1 ;
         15 – примарное число, т.к. 15 = 3 1 · 5 1 .
	
a b : divideble dup rot dup rot / rot * = ;
n : is_primarni 0 swap dup 2 for dup r@ r@ * divideble rot + swap endfor 
    swap 0 = if . ."  - primarnyya " else . ."  - ne primarnyya " then cr ;
	
/// -----------------------------------------------------------
var : 0
  Task : Напишите слово, которое для положительного числа построит последовательность Коллатца.
         Последовательность Коллатца строится так:
           • Если текущий член последовательности делится на два, то делим его пополам.
           • Иначе умножаем его на 3 и прибавляем 1.
         Последовательность Коллатца всегда приходит к единице, но никто не знает, почему.
	
: divideble dup rot dup rot / rot * = ;
n : build_sequence repeat dup . cr dup 2 divideble if 2 / else 3 * 1 + then dup 1 = until . ;
/// -----------------------------------------------------------
var : 2
  Task : Напишите слово, которое найдёт произведение всех простых делителей числа (его радикал).
         Например, для числа 20 это 10, т.к. 20 = 2 2 · 5 1 , его простые делители 2 и 5.

n : count_radikal 0 1 repeat 1 + rot dup rot /
/// --------------------------------------------------------------------------------------




My notes :

@ (addr - значение) Получить значение из памяти.
! (val addr -) Сохранить значение по адресу.
с! (char addr -) Сохранять один байт по адресу.
c@ (addr - char) Чтение одного байта, начиная с адреса.
dp - даёт адрес - начиная откуда уже можно писать

a b : divideble dup rot dup rot / rot * = ;
n : count_dividers 0 swap dup 1 + 1 for dup r@ divideble rot + swap endfor swap ;
n : is_prime count_dividers 2 = if 1 else 0 then cr ; 
kol_bytes n : allot is_prime dp dup rot swap ! ;
kol : asave 0 for r@ dup dp + c! endfor ;
kol : aread 0 for r@ dp + c@ . endfor ;

x id : m_push dp + ! ; - положить х по адресу dp+id. Аналог buf[dp+id] = x
id : m_get dp + @ . ; - вывести содержимое по адресу dp+id. Аналог cout << buf[dp+id];

: m_push dp + ! ;
: m_get dp + @ . ;

