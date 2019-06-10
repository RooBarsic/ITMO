`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05.06.2019 17:42:57
// Design Name: 
// Module Name: control_logic
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

// Основная логика упровления
module control_logic(
    input rst,
    input clk,
    input testing_button_status,
    input sqrt3_button_status,
    input get_lsfr_base_from_data,
    input [7:0] input_data,
    output reg busy,
    output reg [3:0] number_of_testing,
    output reg [7:0] result
);

reg lsfr_rst;
reg lsfr_start;
reg [7:0] lsfr_base_number; 
wire lsfr_busy;
wire [7:0] lsfr_result;
// "функция" генератор чисел LSFR
generate_next_LSFR div1(
    .clk(clk),
    .rst(lsfr_rst),
    .outside_access(lsfr_start),
    .base_number(lsfr_base_number),
    .busy(lsfr_busy),
    .generated_number(lsfr_result)
);

reg sqrt3_rst;
reg sqrt3_start;  // отвечает за старт
reg [7:0] sqrt3_data;  // основное число - от которого надо найти кубический корень
wire sqrt3_busy;  // отвечает за занятость функции
wire [7:0] sqrt3_result;  // тут будет результат ( т.е. кубический корень от sqrt3_data )
// "функция" подсчёта кубического корня от sqrt3_data 
sqrt3 div2(
    .clk_c(clk),
    .rst_c(sqrt3_rst),
    .start_c(sqrt3_start),
    .x(sqrt3_data),
    .result(sqrt3_result),
    .busy(sqrt3_busy)
);

reg crc_rst;
reg [7:0] crc_data;
reg crc_start;
wire crc_busy;
wire [7:0] crc_result;
CRC8_calculator driv3(
    .clk(clk),
    .rst(crc_rst),
    .data(crc_data),
    .new_data(crc_start),
    .busy(crc_busy),
    .result_crc8(crc_result)
);

// Некоторым переменным - дал больше бит - чем им требуется по логике использования/работы
// можете сами их уменьшать
    
reg testing_access;  // бит разрешения тестирования ( если он 0, то мы не сможем активировать само тестирование )
reg sqrt3_access; // бит разрешения вычисления sqrt3 ( если он 0, то мы не сможем активировать вычисление sqrt3 )
reg [3:0] kol_testing = 0;  // тут храним количество тестирований с момента подачи питания ( через rst его НЕ сбрасываем )
reg [8:0] id_test; // т.к. в тестировании нам надо постестить плату на 256 чисел, то тут храним сколько чисел осталось

reg [7:0] commutator; // принимает 3 состояния WAITING CALC_SQRT DO_TESTING
localparam WAITING = 4'b0000;
localparam CALC_SQRT = 4'b0001;
localparam DO_TESTING = 4'b0010;

reg [7:0] sqrt_stage; // хранит этапы тестирования
localparam SQRT_INIT = 4'b0000;  // инициализация/подготовка к вычислению sqrt3 
localparam WAITING_SQRT = 4'b0001; // ждём окончания вычисления sqrt3

reg [7:0] testing_stage; // хранит этапы тестирования
localparam TEST_INIT_BEGIN = 4'b0000;  // начало инициализации/подготовки к тестированию
localparam TEST_INIT_FINISH = 4'b0001;  // конец инициализации/подготовки к тестированию ( этот пункт очень важен )
localparam TEST_GENERATE_NUMBER = 4'b0010;  // Просим LSFR - сгенерить следуюшее число
localparam TEST_WAIT_GENERATOR = 4'b0011;  // Ждём окончания генерации числа
localparam TEST_CALC_SQRT3 = 4'b0100; // Просим SQRT3 - посчитать кубический корень от сгенерированного числа
localparam TEST_WAIT_SQRT3 = 4'b0101; // Ждём окончания работы SQRT3
localparam TEST_CALC_CRC = 4'b0110; // просим CRC8 - добавить результат SQRT3 - в обший "хэш"
localparam TEST_WAIT_CRC = 4'b0111; // Ждём окончания работы CRC8
                                    // Если оказалось что id_test == 0 - переходим в TEST_FINISH
                                    //      Иначе id_test-- и переходим в TEST_GENERATE_NUMBER
localparam TEST_FINISH = 4'b1000; // конец тестирования

always@(posedge clk) begin
    //$display(" ~~~~~~~~~~~~ control logic info : id_test = %d", id_test);
    number_of_testing <= kol_testing;
    if(rst) begin // если пришёл сигнал reset 
        busy <= 0;
        result <= 0;
        commutator <= WAITING;
        
        testing_access <= 1;
        sqrt3_access <= 1;
        
        lsfr_rst <= 1;
        lsfr_start <= 0;
        
        sqrt3_rst <= 1;
        sqrt3_start <= 0;
        
        crc_rst <= 1;
        crc_start <= 0;
     end
    else begin // если сигнала reset - нет, то убираем сигнал rest - который мы дали другим "функциям"
        lsfr_rst <= 0;
        sqrt3_rst <= 0;
        crc_rst <= 0;
     end
    
    /// new adding
    number_of_testing <= kol_testing;
    
    if((sqrt3_access == 1) && (sqrt3_button_status == 1) && (busy == 0)) begin
        // Если есть прищёл сингал на подсчёт sqrt3; и у нас есть разрешение на это; и мы сейчас не заняты, то
        // начинаем шитать sqrt3
        busy <= 1;
        sqrt3_access <= 0;
        commutator <= CALC_SQRT;
        sqrt_stage <= SQRT_INIT;
     end
    else if((testing_access == 1) && (testing_button_status == 1)) begin
        // если нажата кнопка тестирования и есть разрешение на тестирование, то
        if(busy == 0) begin    // если мы сейчас не заняты, то
            // начинаем само тестирование
            busy <= 1;
            testing_access <= 0;
            commutator <= DO_TESTING;
            testing_stage <= TEST_INIT_BEGIN;
         end
        else if((commutator == DO_TESTING) && (testing_stage != TEST_FINISH)) begin
            // иначе еслы мы сейчас заняты и не находимся на последней итерации тестирования, то
            // останавливаем само тестирование
            busy <= 0;
            testing_access <= 0;
            commutator <= WAITING;
         end
     end
    
    if((sqrt3_button_status == 0) && (busy == 0)) sqrt3_access <= 1; // даём разрешение на подсчёт sqrt3
    if((testing_button_status == 0) && (busy == 0)) testing_access <= 1; // даём разрешение на тестирование
    
    case(commutator)
        WAITING : begin
            // ждём команды от пользователя
         end
        CALC_SQRT : begin
            // дали команду на подсчёт sqrt3
            //$display(" ~~~ ## CALC_SQRT ");
            case(sqrt_stage)
                SQRT_INIT : begin
                    // инициализация для подсчёта sqrt3
                    //$display(" ~~~ ## # SQRT INIT");
                    if(sqrt3_start == 0) begin
                        sqrt3_data <= input_data;
                        sqrt3_start <= 1;
                     end
                    else if(sqrt3_busy == 1) sqrt_stage <= WAITING_SQRT;
                 end
                WAITING_SQRT : begin
                    // ждём окончания вычислений
                    //$display(" ~~~ ## # SQRT WAITING ");
                    if(sqrt3_busy == 0) begin
                        //$display(" ~~~ ## # % SQRT busy = 0 data = %d sqrt_result = %d", input_data, sqrt3_result);
                        sqrt3_start <= 0;
                        busy <= 0;
                        commutator <= WAITING;
                        result <= sqrt3_result;
                     end
                 end
             endcase
         end
        DO_TESTING : begin
            // дали команду на тестирование
            //$display(" ~~~ @@ DO_TESTING ");
            case(testing_stage)
                TEST_INIT_BEGIN : begin
                    /// начало подготовки к тестированию
                    //$display(" ~~~ @@ @ TEST_INIT_BEGIN");
                    id_test <= 255; /// Говорим что надо сделать 255 тестов ( если хотите - смените на 256 )  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    crc_rst <= 1;
                    lsfr_rst <= 1;
                    lsfr_start <= 0;
                    if(get_lsfr_base_from_data) lsfr_base_number <= input_data;
                    else lsfr_base_number <= 1;
                    testing_stage <= TEST_INIT_FINISH;
                 end
                TEST_INIT_FINISH : begin
                    /// конец подготовки к тестированию
                    //$display(" ~~~ @@ @ TEST_INIT_FINISH");
                    crc_rst <= 0; // заметьте, мы сменили сигнал reset с 1 на 0 у CRC8 и у LSFR
                    lsfr_rst <= 0;
                    testing_stage <= TEST_GENERATE_NUMBER;
                 end
                TEST_GENERATE_NUMBER : begin
                    /// Просим LSFR - сгенерить следуюшее число
                    //$display(" ~~~ @@ @ TEST_GENERATE_NUMBER");
                    if(lsfr_start == 0) lsfr_start <= 1;
                    else if(lsfr_busy == 1) testing_stage <= TEST_WAIT_GENERATOR;
                 end
                TEST_WAIT_GENERATOR : begin
                    /// Ждём окончания генерации от LSFR
                    //$display(" ~~~ @@ @ TEST_WAIT_GENERATOR");
                    if(lsfr_busy == 0) begin
                        /// Когда LSFR - закончил генерацию - сменим сигнал lsfr_start на 0 и идём дальще
                        //$display(" ~~~ @@ @ % TEST GENERATOR busy = 0 ");
                        lsfr_start <= 0;
                        testing_stage <= TEST_CALC_SQRT3;
                     end
                 end
                TEST_CALC_SQRT3 : begin
                    /// Просим SQRT3 - посчитать кубический корень от lsfr_result
                    //$display(" ~~~ @@ @ TEST_CALC_SQRT");
                    sqrt3_data <= lsfr_result;
                    if(sqrt3_start == 0) sqrt3_start <= 1;
                    else if(sqrt3_busy == 1) testing_stage <= TEST_WAIT_SQRT3;
                 end
                TEST_WAIT_SQRT3 : begin
                    /// Ждём окончания подсчёта корня
                    //$display(" ~~~ @@ @ TEST_WAIT_SQRT");
                    if(sqrt3_busy == 0) begin
                        /// Когда подсчёт корня завершон - сменим сигнал sqrt3_start на 0 и идём дальще
                        //  Last BUG    ??????????????????   $display(" KUKUKUKUKUKU ~~~ @@ @ % TEST SQRT FINISH     x = %d sqrt_result = %d ", lsfr_result, sqrt3_result);
                        sqrt3_start <= 0;
                        testing_stage <= TEST_CALC_CRC;
                     end
                 end
                TEST_CALC_CRC : begin
                    /// Просим CRC8 - добавить sqrt3_result в общий "хэш"
                    //$display(" ~~~ @@ @ TEST_CALC_CRC   crc_start = %d crc_busy = %d", crc_start, crc_busy);
                    crc_data <= sqrt3_result;
                    if(crc_start == 0) crc_start <= 1;
                    else if(crc_busy == 1) testing_stage <= TEST_WAIT_CRC;
                 end
                TEST_WAIT_CRC : begin
                    /// Ждём окончания работы CRC8
                    //$display(" ~~~ @@ @ TEST_WAIT_CRC");
                    if(crc_busy == 0) begin
                        /// Когда добавление в "хэш" завершено
                        //  Last BUG    ??????????????????   $display(" ~~~ @@ @ % TEST CRC FINISH");
                        crc_start <= 0;  /// сменим сигнал crc_start на 0
                        result <= crc_result;  /// выводим на светодиоды ответ от CRC8
                        if(id_test == 0) begin   /// если сделали все 255 тестов, то диём на последнюю стадию тестирования
                            testing_stage <= TEST_FINISH;
                            kol_testing <= kol_testing + 1;
                         end
                        else begin  /// если мы не провели ещё все тесты, то идём в TEST_GENERATE_NUMBER 
                            id_test <= id_test - 1;
                            testing_stage <= TEST_GENERATE_NUMBER;
                         end
                     end
                 end
                TEST_FINISH : begin /// Конец тестирования
                    //$display(" ~~~ @@ @ TEST_FINISH"); 
                    busy <= 0;  /// говорим что мы больше не заняты ( Доби теперь свободен )
                    number_of_testing <= kol_testing; /// выводим на светодиоды количество циклов тестирования 
                    /// в каждом цикле тестирования - мы проводили 255 (256) тестов
                    result <= crc_result;  /// выводим на светодиоды итоговый "хэш" полученный от CRC8
                    commutator <= WAITING;  /// переходим в режим ожидания команды
                 end
             endcase
         end
     endcase
end    
endmodule




