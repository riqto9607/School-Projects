package assignment;

public class UserInfo {
	
    private String name;
    private String userID;
    
    public UserInfo() {
        name = " ";
        userID = " ";
    }
    
    public String getName() {
        return name;
    }

    public String getUserID() {
        return userID;
    }

    public void setName(String name) {
    	this.name = name;
    }
    
    public void setID(String userID) {
    	this.userID = userID;
    }

  // Validate the name and assign userID
	public void obtainName(String name) {
		setName(name);
			
		if (name.contains(" ")) {
			int index = name.lastIndexOf(" ");
			userID = name.substring(0, 1).toUpperCase() + 
					name.substring(index + 1, index + 2).toUpperCase() + name.substring(index + 2);
		}
  		else 
  			userID = "guest";
		
	}

   
}