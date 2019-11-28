select
	last_name.value as `фамилия`,
	first_name.value as `имя`, 
	patronymic.value as `отчество`, 
	sum(rating.ratingtypeShort) as `суммарный рейтинг`
from lessons
	inner join student on lessons.idStudent = student.id
	inner join last_name on student.last_name_id = last_name.id 
	inner join first_name on student.first_name_id = first_name.id 
	inner join patronymic on student.patronymic_id = patronymic.id 
	inner join rating on lessons.idRating = rating.id
group by student.id;