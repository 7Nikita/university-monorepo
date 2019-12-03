select 
	last_name.value as `фамилия`, 
	first_name.value as `имя`,
	patronymic.value as `отчество`, 
	count(distinct ratingtypeShort) as `Количество уникальных значений`, 
	avg(ratingtypeShort) as `Средний рейтинг`,
	min(ratingtype.ratingtypeShort) as `Минимальный рейтиг`, 
	max(ratingtype.ratingtypeShort) as `Максимальный рейтиг`,
	count(ratingtypeShort) as `Количество оценок рейтинга`
from lessons
	inner join students on students.id = lessons.idStudent
	inner join last_name on last_name.id = students.name1 
	inner join first_name on first_name.id = students.name2 
	inner join patronymic on patronymic.id = students.name3 
	inner join ratingtype on ratingtype.id = lessons.idRating
where last_name.value like 'Сид%'
group by lessons.idCurs, students.id, date_format(lessons.Date,"%d.%c.%Y");
