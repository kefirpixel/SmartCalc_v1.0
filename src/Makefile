CC := gcc 
CFLAGS := -Wall -Wextra -Werror -std=c11 -fprofile-arcs -ftest-coverage
LDFLAGS := -lcheck -lgcov -fprofile-arcs --coverage

ifeq ($(shell uname), Linux)
    LDFLAGS += -lpthread -lrt -lm -lsubunit
    OPEN_CMD := xdg-open
else ifeq ($(shell uname), Darwin)
    LDFLAGS += -lm
    OPEN_CMD := open
endif

all: clean install 
SRC := $(wildcard backend/*.c) 
OBJ = $(patsubst backend/%.c, obj/%.o, $(SRC))
OBJ_GCOV = $(patsubst backend/%.c, gcov_obj/%.o, $(SRC))
TEST_SRC := $(wildcard tests/test_*.c)
TEST_OBJ = $(patsubst tests/%.c, tests/%.o, $(TEST_SRC))

TARGET := SmartCalc_v1_0


obj/%.o: backend/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

gcov_obj/%.o: backend/%.c 
	@$(CC) $(CFLAGS) $(GCOVFLAGS) -c $< -o $@

smart_calc.a: $(OBJ)
	@ar -src $@ $(OBJ)

smart_calc_gcov.a: $(OBJ_GCOV) 
	@ar -src $@ $(OBJ_GCOV)

test: tests/tests.o smart_calc_gcov.a 
	@$(CC) -g $< smart_calc_gcov.a -o $@ $(LDFLAGS) $(GCOVFLAGS)
	@clear
	@./$@ 

install: uninstall  
	@clear
	@echo "Installation"
	@mkdir -p ../build
	@cd frontend/SmartCalc_v1_0/ && qmake && make && make clean && rm -rf Makefile && mv $(TARGET).app ../../../build
	@cp -R ../build/$(TARGET).app ~/Desktop/$(TARGET).app
	@echo "Calculator installed"

uninstall:
	@rm -rf ../build/$(TARGET).app
	@rm -rf ~/Desktop/$(TARGET).app
	@echo "Calculator removed"

dvi: 
	open s21_specification/s21_SmartCalc.md

dist: 
	@mkdir -p ../dist
	@cp -R ../build/$(TARGET).app ../dist
	@cp ../README_RUS.md ../dist && cp ../README.md ../dist
	@cd ../dist && tar cvzf $(TARGET).tgz *
	@cd ../dist && rm -rf $(TARGET).app README.md README_RUS.md

gcov_report: test 
	lcov -c -d gcov_obj/. -o gcov_obj/coverage.info
	genhtml gcov_obj/coverage.info --output-directory out
	$(OPEN_CMD) out/index.html

clean: 
	@rm -rf ../build ../dist gcov_obj/*.o test
	@rm -rf gcov_obj/*.gcda gcov_obj/*.gcno 
	@rm -rf gcov_obj/*.info out *.a *.gcno tests/tests.o qt/*
	@rm -rf ../.DS_Store .DS_Store ../.vscode ui/.DS_Store
	@rm -rf tests/*.gcda tests/*.gcno frontend/build-SmartCalc*

clang: 
	@clang-format -i -style=GOOGLE backend/*.c backend/*.h tests/*.c frontend/SmartCalc_v1_0/*.cpp frontend/SmartCalc_v1_0/*.h frontend/SmartCalc_v1_0/*.ui

style: 
	@clang-format -n -style=GOOGLE backend/*.c backend/*.h tests/*.c frontend/SmartCalc_v1_0/*.cpp frontend/SmartCalc_v1_0/*.h frontend/SmartCalc_v1_0/*.ui

cppcheck: clean test 
	@cppcheck --enable=all --suppress=missingIncludeSystem backend/ frontend/SmartCalc_v1_0/

valgrind: clean test 
	@CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test

leaks: clean test 
	@leaks -atExit -- ./test