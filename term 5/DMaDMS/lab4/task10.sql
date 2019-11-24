select
last_name.value as `фамилия`, first_name.value as `имя`, patronymic.value as `отчество`,
country.name as `страна`, region.name as `область`, district.name as `район`, city.type as `тип_города`,
city.name as `город`, street.type as `тип_улицы`, street.name as `улица`, address.house_number as `дом`,
address.house_pavilion as `корпус`, address.flat_number as `квартира`
from student
inner join first_name on student.first_name_id = first_name.id
inner join last_name on student.last_name_id = last_name.id
inner join patronymic on student.patronymic_id = patronymic.id
inner join address on student.address_id = address.id
inner join country on address.country_id = country.id
inner join district on address.distirct_id = district.id
inner join region on address.region_id = region.id
inner join city on address.city_id = city.id
inner join street on address.street_id = street.id