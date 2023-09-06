import javax.swing.*;

// Interface for threads that can be incremented
interface IncrementThread {
    void run();
}

// Class representing a custom semaphore thread
class CustomSemaphoreThread extends Thread implements IncrementThread {
    private int increment;
    private IncrementSlider mySlider;
    private int count;
    private static int DelayBound = 100000; // Used for delay
    private static int THREAD_COUNTER = 0;
    private int curNum;

    public CustomSemaphoreThread(IncrementSlider mySlider, int increment, int priority) {
        this.mySlider = mySlider;
        this.increment = increment;
        curNum = ++THREAD_COUNTER;
        setPriority(priority);
    }

    @Override
    public void run() {
        while (TaskB.semafor != 0) ; // Wait for semaphore to be free
        TaskB.semafor = 1; // Acquire semaphore

        while (!interrupted()) {
            ++count;
            if (count > DelayBound) {
                mySlider.Increase(increment);
                count = 0;
            }
        }

        TaskB.semafor = 0; // Release semaphore
    }

    public JPanel GetJPanel() {
        JPanel panel = new JPanel();

        JLabel label = new JLabel("Thread #" + curNum + ", Increment = " + increment);
        SpinnerModel sModel = new SpinnerNumberModel(getPriority(), Thread.MIN_PRIORITY, Thread.MAX_PRIORITY, 1);
        JSpinner Spinner = new JSpinner(sModel);
        Spinner.addChangeListener(e -> {
            setPriority((int) (Spinner.getValue()));
        });
        panel.add(label);
        panel.add(Spinner);
        return panel;
    }
}

// Main class
public class TaskB {
    public static volatile int semafor;

    public void run() {
        JFrame MainFrame = new JFrame();
        MainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        MainFrame.setSize(600, 200);
        IncrementSlider mySlider = new IncrementSlider();

        var ThreadsRef = new Object() {
            CustomSemaphoreThread thread1, thread2;
        };

        JButton start1Btn = new JButton("Start 1");
        JButton start2Btn = new JButton("Start 2");

        JButton stop1Btn = new JButton("Stop 1");
        JButton stop2Btn = new JButton("Stop 2");

        start1Btn.addActionListener(e -> {
            ThreadsRef.thread1 = new CustomSemaphoreThread(mySlider, -1, Thread.MIN_PRIORITY);
            ThreadsRef.thread1.start();

            start1Btn.setEnabled(false);
            stop1Btn.setEnabled(true);
        });

        start2Btn.addActionListener(e -> {
            ThreadsRef.thread2 = new CustomSemaphoreThread(mySlider, +1, Thread.MAX_PRIORITY);
            ThreadsRef.thread2.start();

            start2Btn.setEnabled(false);
            stop2Btn.setEnabled(true);
        });

        stop1Btn.addActionListener(e -> {
            ThreadsRef.thread1.interrupt();
            start1Btn.setEnabled(true);
            stop1Btn.setEnabled(false);
        });

        stop2Btn.addActionListener(e -> {
            ThreadsRef.thread2.interrupt();
            start2Btn.setEnabled(true);
            stop2Btn.setEnabled(false);
        });

        JPanel MainFramePanel = new JPanel();
        MainFramePanel.setLayout(new BoxLayout(MainFramePanel, BoxLayout.Y_AXIS));
        MainFramePanel.add(mySlider);

        JPanel jPanel = new JPanel();
        jPanel.add(start1Btn);
        jPanel.add(start2Btn);

        JPanel jPanel2 = new JPanel();
        jPanel2.add(stop1Btn);
        jPanel2.add(stop2Btn);

        JPanel labelPanel = new JPanel();
        JLabel statusLabel = new JLabel();

        labelPanel.add(statusLabel);

        statusLabel.setText("Free");

        MainFramePanel.add(labelPanel);
        MainFramePanel.add(jPanel);
        MainFramePanel.add(jPanel2);

        MainFrame.setContentPane(MainFramePanel);
        MainFrame.setVisible(true);
    }



}
