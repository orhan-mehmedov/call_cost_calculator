Constraints:

Due to not full/clear requirements following constraints were added:
- call can not be longer than 12h
- exact time for date last credit added also must be entered 
- date / time format is "%Y-%m-%d %H:%M:%S"
- it is assumed that free minites used must be calculated with precision 1s
and then if any non-free call minutes duirng the call - to be ceiled to a minute
- some constrainst about formats and values, negative values not allowed
- weekends first 5 minutes free for all has more priority than free 
minutes inside opartor, so during weekend 5 minutes free - free minutes
inside oprator are not consumed
- operator prefix is at least 3 digits
- number called can not be les or equal to operator prefix length

Settings, input, how to test:
- it is a program that works at the command line and uses arguments
example:
./call_cost_calculator frontend=NO subscriber_account=./test_case_1.txt call_start_date_time=2016-06-06 10:10:00 call_end_date_time=2016-06-06 10:20:00 number_called=1234567890

frontend means here that it is in user interactive mode (the only mode for now)
subscriber_account is the call "context" file with vairous settings (free minutes etc.)
others are parameters of for the call requested to be calculated

There is a special test directory ./test with a test script and settings file examples
There is a fully automated test test.sh (do not forget to build first)

Source code is in ./code
./build contains object files as a result of the compilation.
./bin contains the ready-to-use stand-alone selfcontained product 
with no dependency other than - for example:
$ ldd ./call_cost_calculator 
        linux-vdso.so.1 (0x00007ffed27e4000)
        libstdc++.so.6 => /usr/lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007fbf24554000)
        libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007fbf24253000)
        libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007fbf2403d000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fbf23c92000)
        /lib64/ld-linux-x86-64.so.2 (0x00007fbf2485f000)

and currently is named "call_cost_calculator"

How to build (under linux):

go to  ./source and just call make celan all

There are no compiler warning though I enabled as much warning flags as possible.
All automated tests have passed OK.

Binaries are not supplied - only sources.

For more information you can reach me here:
http://mehmed.info/

License is GPL v3. I'll make it available online / github sooner (or later).

Regards,
O.M.

