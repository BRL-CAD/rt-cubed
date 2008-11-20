package stractThread;

public interface STRunnable extends Runnable {
	
	public void start();
	public Thread getThread();
	public void stop();
	public boolean getRunStatus();
	public boolean getRunCmd();
}
