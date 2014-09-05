Multigrep -- a small tool for multiline text searching.

v0.1
==============
    
        USAGE: ./multigrep -s 'start' -e 'end' [-n 'negative match'] 'match'

    OPTIONS:
            -e      ending regex
            -h      print this help
            -s      starting regex
            -v      version information


Multigrep's use case is for finding multiple matching nodes in unstructured or semi-structured text. For example, take the below partial logfile.


    <Log>
    time: 09:45:22
    Stack Trace: Important Error
        ... on line 32
    </Log>
    <Log>
    time: 11:13:23
    Stack Trace: Important Error
        ... Unimportant condition
    </Log>

to return only the first entry, one might use the following command:

    ./multigrep -s '<Log>' -e '</Log>' -n 'Unimportant condition' 'Important Error' < logfile.log > errors.log
