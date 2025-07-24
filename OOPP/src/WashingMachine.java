package assignment;

public class WashingMachine extends Product {

	private String machineFunction;
	private String machineColor;
	private int washingCapacity;

	public WashingMachine(int itemNo, String productName, int productQuantity, double productPrice,
			String function, String color, int capacity) {
		super(itemNo, productName, productQuantity, productPrice);
		machineFunction = function;
		machineColor = color;
		washingCapacity = capacity;
	}

	public String getMachineFunction() {
		return machineFunction;
	}

	public void setMachineFunction(String machineFunction) {
		this.machineFunction = machineFunction;
	}

	public String getMachineColor() {
		return machineColor;
	}

	public void setMachineColor(String machineColor) {
		this.machineColor = machineColor;
	}

	public int getWashingCapacity() {
		return washingCapacity;
	}

	public void setWashingCapacity(int washingCapacity) {
		this.washingCapacity = washingCapacity;
	}

	public double inventoryValue() {
		return getProductPrice() * getProductQuantity();
	}

	@Override
	public String toString() {
		return "\nItem number\t\t: " + getItemNumber() + "\n" + "Product name\t\t: " + getProductName() + "\n"
				+ "Function\t\t\t: " + machineFunction + "\n" + "Color\t\t\t: " + machineColor + "\n"
				+ "Volume (in kg)\t: " + washingCapacity + "\n" + "Quantity available\t: " + getProductQuantity()
				+ "\n" + "Price (RM)\t\t: " + getProductPrice() + "\n" + "Inventory value (RM): " + inventoryValue()
				+ "\n" + "Product status\t\t: " + isProductStatus() + "\n";
	}
}
