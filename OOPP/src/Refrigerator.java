package assignment;


public class Refrigerator extends Product{

	private String doorDesign;
	private String doorColor;
	private int doorCapacity;
	
	public Refrigerator(int itemNo, String productName, int productQuantity, double productPrice, String design, String color, int capacity) {
		super(itemNo, productName, productQuantity, productPrice);
		doorDesign = design;
		doorColor = color;
		doorCapacity = capacity;
	}

	public String getDoorDesign() {
		return doorDesign;
	}

	public void setDoorDesign(String doorDesign) {
		this.doorDesign = doorDesign;
	}

	public String getDoorColor() {
		return doorColor;
	}

	public void setDoorColor(String doorColor) {
		this.doorColor = doorColor;
	}

	public int getDoorCapacity() {
		return doorCapacity;
	}

	public void setDoorCapacity(int doorCapacity) {
		this.doorCapacity = doorCapacity;
	}
	
	public double inventoryValue() {
		return getProductPrice() * getProductQuantity();
	}
	
	@Override
	public String toString() {
		return "\nItem number\t\t: " + getItemNumber() +  "\n" +
				"Product name\t\t: " + getProductName() +  "\n" +
				"Door design\t\t: " + doorDesign +  "\n" +
				"Color\t\t\t: " + doorColor +  "\n" +
				"Capacity (in Litres)\t: " + doorCapacity +  "\n" +
				"Quantity available\t: " + getProductQuantity() +  "\n" +
				"Price (RM)\t\t: " + getProductPrice() +  "\n" +
				"Inventory value (RM): " + inventoryValue() + "\n" +
				"Product status\t\t: " + isProductStatus() + "\n";
	}
	
}
