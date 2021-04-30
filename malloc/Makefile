
target = target
src = $(shell find -name "*.c")
inc = $(shell find -name "*.h")
obj = $(src:%.c=%.o)
libs = -lpthread

ALL = $(target)
$(target) : $(obj)
	gcc $(obj) -o $(target) $(libs)

%.o : %.c $(inc)
	gcc -c $< -o $@

.PHONY : clean
clean:
	-rm -rf $(ALL) $(obj)
	    
