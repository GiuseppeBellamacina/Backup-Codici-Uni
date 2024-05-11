/*
 * @Test - MAIN Program logic place
 * @BeforeClass - Executes before the first test method of the class
 * @AfterClass - Executes after all the test methods of the current class
 * @BeforeMethod - Executes before each test method
 * @AfterMethod - Executes after each test method
*/

import org.testng.Assert; // Assert.assertEquals
import org.testng.annotations.*; // @Test, @BeforeClass, @AfterClass, @BeforeMethod, @AfterMethod

public class StackTest {
    Stack<Integer> s;

    @BeforeClass
    public void setup(){
        s = new Stack<Integer>(100);
    }

    @Test(dataProvider = "testData")
    public void aTest(int n) throws StackOverflowException, StackUnderflowException {
        s.push(n);
        int r = s.pop();
        System.out.println("Fast test " + n + " " + r);
        Assert.assertEquals(n, r);
    }

    @Test
    public void anotherTest(){
        System.out.println("Another test");
    }

    @DataProvider(name = "testData")
    public Object [][] provideData(){
        return new Object [][]{
            {10},
            {20},
            {30},
            {40},
            {50},
            {60},
            {70},
            {80},
            {90},
            {100}
        };
    }
}