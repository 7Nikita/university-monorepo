select 
	last_name.value as `фамилия`, 
	first_name.value as `имя`,
	patronymic.value as `отчество`, 
	lessons.idCurs as 'по предмету',
	sum(ratingtypeShort) / count(*) as 'средний рейтинг', 
	min(ratingtypeShort) as 'минимальный рейтинг', 
	max(ratingtypeShort) as 'максимальный рейтинг', 
	count(ratingtypeShort) as 'кол-во оценок', 
	lessons.Date as 'дата сдачи'  
from lessons
	inner join students on students.id = lessons.idStudent
	inner join last_name on last_name.id = students.name1 
	inner join first_name on first_name.id = students.name2 
	inner join patronymic on patronymic.id = students.name3 
	inner join ratingtype on ratingtype.id = lessons.idRating
where last_name.value like 'Вор%'
group by students.id, lessons.idCurs, lessons.Date;