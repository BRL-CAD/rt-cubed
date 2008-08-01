package stractThread;

public interface STPauseable extends STRunnable {

	public void enable();
	public void disable();
	public boolean isEnabled();

}
