package zadanie2;

import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.junit.jupiter.MockitoExtension;
import org.junit.jupiter.api.*;
import org.mockito.*;


@ExtendWith(MockitoExtension.class)
public class GenericDAOTest {
    @Mock
    Session session = Mockito.mock(Session.class);

    @Mock
    DbLogger dbLogger = Mockito.mock(DbLogger.class);

    @InjectMocks
    GenericDAO genericDAO = new GenericDAO();

    @Captor
    ArgumentCaptor<Exception> exceptionArgumentCaptor;

    Object object = new Object();

    @Test
    public void testSave() throws SessionOpenException {
        genericDAO.setSession(session);
        Mockito.doThrow(SessionOpenException.class).when(session).open();
        Assertions.assertThrows(SessionOpenException.class, () -> genericDAO.save(object));
    }

    @Test
    public void testSave2() throws SessionOpenException, CommitException {
        genericDAO.setSession(session);
        genericDAO.setDbLogger(dbLogger);
        Mockito.doThrow(CommitException.class).when(session).commitTransaction();
        genericDAO.save(object);
        Mockito.verify(dbLogger).log(exceptionArgumentCaptor.capture());
        Assertions.assertTrue(exceptionArgumentCaptor.getAllValues().stream().findFirst().get() instanceof CommitException);
    }
}
