select
	last_name.value as `фамилия`,
	first_name.value as `имя`, 
	patronymic.value as `отчество`, 
	lessons.idLessonsType as `предмет`, 
	min(rating.ratingtypeShort) as `минимальный рейтинг`, 
	max(rating.ratingtypeShort) as `максимальный рейтинг`
from lessons
	inner join students on lessons.idStudent = students.id 
	inner join first_name on students.name2 = first_name.id 
	inner join last_name on students.name1 = last_name.id
	inner join patronymic on students.name3 = patronymic.id 
	inner join rating on lessons.idRating = rating.id
group by students.id, lessons.idLessonsType;