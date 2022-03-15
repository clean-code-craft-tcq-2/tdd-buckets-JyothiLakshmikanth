# Test Driven Ranges

The charging current varies during the process of charging.
We need to capture the range of current measurements -
what range of currents are most often encountered while charging.

> **DO NOT** jump into implementation! Read the example and the starting task below.

## Example

### Input

Consider a set of periodic current samples from a charging session to be:
`3, 3, 5, 4, 10, 11, 12`

### Functionality

The continuous ranges in there are: `3,4,5` and `10,11,12`.

The task is to detect the ranges and
output the number of readings in each range.

In this example,

- the `3-5` range has `4` readings
- the `10-12` range has `3` readings.

### Output

The expected output would be in comma-separated (csv format):

```
Range, Readings
3-5, 4
10-12, 3
```

## Tasks

Establish quality parameters: 

- What is the maximum complexity (CCN) per function?CNN=5
- How many lines of duplicate code will you tolerate? No Duplication beyond 5 lines
- Ensure 100% line and branch coverage at every step. Include the coverage yml in the workflows.

Adapt/adopt/extend the `yml` files from one of your previous workflow folders.

Start Test-driven approach

1. Write the smallest possible failing test: give input `4,5`. assert output to be `4-5, 2`.
1. Write the minimum amount of code that'll make it pass.
1. Refactor any assumptions, continue to pass this test. Do not add any code without a corresponding test.

Flow :

![alt text](https://www.planttext.com/api/plantuml/png/RP7DJiCm48JlVegLJu3KLq1523YW8bH-BgW7DvuaLfDryAu3VNkSfZaWkAt6CzzwxBMeIvhxpfYBgqjQhQx9Dj3N5biu7xYH-nJxXp22N_2PmHLks3_YQ4seoIuQ1Q5trmLlILkmeOdqeIbZHxOEx0jm4xX4D-xxAVTxf8bRr8LWvmpPsmIdc32qTTn0QEy4dYAVjCEq-cnz6_nYPOWMquXAOwAleErCE9VupKWdxdyRAncfZgbtIbbAy2zxIPNNCkW4vjIqTcKiLGNi2VsWHufPXwnsFh_ZwHhqd685aTsSBbfjZ5cNeNp03m00)

Test Use cases:

1. Operation Action : Check for Valid/InValid Sequence. 
    Expected Results : Check for breach Type. If Valid Sequence Breach Type would be VALID and if it is InValid Sequence Breach Type would be INVALID
1. Operation Action : For Valid Sequence check for Max and Min Value.
    Expected Action : check if the Max and Min Value that is found from the Valid Sequence is as expected Value
1. Operation Action : For Valid Sequence check the Readings
    Expected Action : Compare the Actual and expected Readings
