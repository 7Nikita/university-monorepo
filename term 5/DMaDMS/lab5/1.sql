select 
	last_name.value as `фамилия`, 
	first_name.value as `имя`,
	patronymic.value as `отчество`, 
	country.name as `страна`, 
	region.name as `область`,
	district.name as `район`, 
	city.name as `город`, 
	city.type as `тип_города`,
	street.type as `тип_улицы`,
	street.name as `улица`, 
	address.house_number as `дом`, 
	address.house_pavilion as `корпус`, 
	address.flat_number as `квартира`
from lessons
	inner join students on lessons.idStudent = students.id 
	inner join last_name on last_name.id = students.name1 
	inner join first_name on first_name.id = students.name2 
	inner join patronymic on patronymic.id = students.name3 
	inner join address on students.address_id = address.id 
	inner join country on address.country_id = country.id 
	inner join region on address.region_id = region.id
	inner join district on address.distirct_id = district.id
	inner join city on address.city_id = city.id
	inner join street on address.street_id = street.id
where students.id = 3;
