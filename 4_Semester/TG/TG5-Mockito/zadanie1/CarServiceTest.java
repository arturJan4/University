package zadanie1;

import org.junit.jupiter.api.*;
import org.mockito.*;

import java.util.HashMap;

public class CarServiceTest {
    @Mock
    CarDAO carDAO = Mockito.mock(CarDAO.class);

    @InjectMocks
    CarService carService = new CarService();

    Car car = new Car();

    @Test
    public void testFindMileageBetweenYears() {
        carService.setEntityManager(carDAO);
        car.setId(1L);
        HashMap<String, Long> hashMap = new HashMap<>();

        hashMap.put("2015", 100L);
        hashMap.put("2016", 200L);
        hashMap.put("2017", 300L);
        hashMap.put("2018", 400L);
        hashMap.put("2019", 500L);
        hashMap.put("2020", 600L);

        car.setYearMileage(hashMap);
        Mockito.when(carDAO.findById(1L)).thenReturn(car);
        Assertions.assertEquals(2100L, carService.findMileageBetweenYears(1L, "2015", "2020"));
    }
}
