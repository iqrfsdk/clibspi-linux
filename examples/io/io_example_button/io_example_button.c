/*
 * Copyright 2015 MICRORISC s.r.o.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <linux/types.h>
#include <sysfs_gpio.h>
#include <machines_def.h>

#define NANO_SECOND_MULTIPLIER  1000000  // 1 millisecond = 1,000,000 nanoseconds
const long INTERVAL_MS = 10 * NANO_SECOND_MULTIPLIER;

int main(void) {
    int ret = 0;
    int i = 0;

    struct timespec sleepValue = {0, INTERVAL_MS};

    printf("Button usage example \n");

    // enable access to GPIOs
    ret = gpio_setup(LED_GPIO, GPIO_DIRECTION_OUT, 0);
    ret |= gpio_setup(BUTTON_GPIO, GPIO_DIRECTION_IN, 0);
    if (ret)
	    return;

    // 10 s loop for button testing
    for (i = 0; i < 1000; i++) {
	int val = gpio_getValue(BUTTON_GPIO);
	if (val)
		gpio_setValue(LED_GPIO, 1);
	else
		gpio_setValue(LED_GPIO, 0);

        // sleep for 10 ms
        nanosleep(&sleepValue, NULL);
    }

    // finish the library
    gpio_cleanup(LED_GPIO);
    gpio_cleanup(BUTTON_GPIO);

    return 0;
}
