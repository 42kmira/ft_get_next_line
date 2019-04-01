# get_next_line

<br>
<img align="left" height="250" src="https://github.com/MrColour/get_next_line/blob/master/resources/Untitled%202.png" />
<br>

This is a rough draft of my get_next_line. It passed Moulinette with a score of 125.
I say it is a rought draft because it isn't cleaned up as I would like. I also realized
that some of the variables had become useless because I stored the linked_buffers
in an array. I had wanted to have a two dimension linked list. One dimension for the current 
line and another for the the other fd's, in which case I would need a pointer to the next_fd link, and
a fd identifier.

<br>
<img height="125" src="https://github.com/MrColour/get_next_line/blob/master/resources/Untitled%203.png" />
<br>

What is the benifit of coding it this way?
Performance.

Most people do something like a strjion, which allocates a new malloc space with 'junk values' that have to
be filled in once again before the appending/joining of the strings begins.

Take for example the string "Slow\n" and a BUFF_SIZE of 1.
 - First strjoin would take "" and "S" and copy "S"
 - Second strjoin would take "S" and "l" and copy "Sl"
 - Third strjoin would take "Sl" and "o" and copy "Slo"
 - Fourth strjoin would take "Slo" and "w" and copy "Slow"

Notice this copies "S" four times plus "l" three times plus "o" twice plus "w" once.
A total of 10 copied characters.

What if there was a way link "S" to "l" to "o" to "w" then malloc for 4 
and then copy the "S" then the "l" then the "o" then the "w".
A total of 4 characters copied.

The time complexities of these two methods are on different levels. One is linear O(n) and the other is O(n<sup>2</sup>).
Notice the strjoin method is a linear summation, hence O(n<sup>2</sup>).

As always the code posted is straight from a git clone from what I turned in.
