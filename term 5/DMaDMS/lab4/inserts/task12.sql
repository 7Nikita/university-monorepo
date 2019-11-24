insert into phone_number (id, country_code_id, operator_code, value)
values
(1, (select id from country where name='Республика Беларусь'), 33, 1111111),
(2, (select id from country where name='Республика Беларусь'), 29, 2222222),
(3, (select id from country where name='Республика Беларусь'), 29, 3333333),
(4, (select id from country where name='Республика Беларусь'), 44, 4444444),
(5, (select id from country where name='Республика Беларусь'), 33, 5555555),
(6, (select id from country where name='Республика Беларусь'), 33, 6666666),
(7, (select id from country where name='Республика Беларусь'), 44, 7777777),
(8, (select id from country where name='Республика Беларусь'), 33, 8888888),
(9, (select id from country where name='Российская Федерация'), 770, 9999999), (10, (select id from country where name='Российская Федерация'), 774, 1010101);