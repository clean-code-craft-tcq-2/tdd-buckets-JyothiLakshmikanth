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

![alt text](https://www.planttext.com/api/plantuml/png/RP3DJiGm38JlUGeh9q3QLq2Bq8B4gWWjFnVKWxTnqq3hW9CkxDlZj5i996xMQEQpn-kKKV8uzCQSNPp3QdK9rbD-wcX7w0BxT2Dnk0q7uaVw78aRkcAtfQCreGMxQ10Il60Vd8NS4HiefDSi8zLWsy1EWLLWZLRuVJyEUvB2LNKXs3a3zbe8CnKCx90z9TXZ8WUH9-szh3vPdp_SOdr3xzM48dY4hv2x6N3gy1SX4_Q_XKqwG1jbm0nZqk0atlr2Bo7zbQ4-aPbwjgXZNRx13ZOYKQ2YbD2NLiMmuN86F4XiLA_dk6gjCMQjW_x_1m00)

Test Use cases:

1. Operation Action : Check for Valid/InValid Sequence. 
    Expected Results : Check for breach Type. If Valid Sequence Breach Type would be VALID and if it is InValid Sequence Breach Type would be INVALID
1. Operation Action : If it is InValid Sequence Error Message to be sent to client
    Expected Results : Error INVALID-SEQUENCE to be sent
1. Operation Action : For Valid Sequence check for Max and Min Value.
    Expected Action : check if the Max and Min Value that is found from the Valid Sequence is as expected Value
1. Operation Action : For Valid Sequence check the Readings
    Expected Action : Compare the Actual and expected Readings
