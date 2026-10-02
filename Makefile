.RECIPEPREFIX := >

APP_DIR = app
DRIVER_DIR = driver

all:
>$(MAKE) -C $(DRIVER_DIR)
>g++ -Iinclude $(APP_DIR)/pulse_generator.cpp -o $(APP_DIR)/pulse_generator
>g++ -Iinclude $(APP_DIR)/analytics.cpp -o $(APP_DIR)/analytics
>g++ -Iinclude $(APP_DIR)/reset_counter.cpp -o $(APP_DIR)/reset_counter

driver:
>$(MAKE) -C $(DRIVER_DIR)

apps:
>g++ -Iinclude $(APP_DIR)/pulse_generator.cpp -o $(APP_DIR)/pulse_generator
>g++ -Iinclude $(APP_DIR)/analytics.cpp -o $(APP_DIR)/analytics
>g++ -Iinclude $(APP_DIR)/reset_counter.cpp -o $(APP_DIR)/reset_counter

clean:
>$(MAKE) -C $(DRIVER_DIR) clean
>rm -f $(APP_DIR)/pulse_generator
>rm -f $(APP_DIR)/analytics
>rm -f $(APP_DIR)/reset_counter
