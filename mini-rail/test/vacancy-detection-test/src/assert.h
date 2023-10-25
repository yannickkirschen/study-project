#include "rail/vacancy.h"

void assert(rail_vacancy_t *v, rail_contact_point_t *points[], int number_points);
void assertError(rail_vacancy_t *v, rail_contact_point_t *points[], int number_points, int error_code);
void assertWithChange(rail_vacancy_t *v, rail_contact_counter_t *counter, rail_contact_point_t *points_before[], int number_points_before, rail_contact_point_t *points_after[], int number_points_after);
