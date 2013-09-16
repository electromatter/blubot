#ifndef PWM_H
#define PWM_H

void pwm_init(void);
void pwm_enable(int en);
void pwm_timer(void);
void pwm_set(char *val);

#endif
