select
last_name.value as last_name as `фамилия`, first_name.value as `имя`, patronymic.value as `отчество`,
university.name as `университет`, faculty.name as `факультет`, specialization.name as `специальность` from student
inner join first_name on student.first_name_id = first_name.id
inner join last_name on student.last_name_id = last_name.id
inner join patronymic on student.patronymic_id = patronymic.id
inner join university on student.university_id = university.id
inner join faculty on student.faculty_id = faculty.id
inner join specialization on student.specialization_id = specialization_id;