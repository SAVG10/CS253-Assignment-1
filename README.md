# CAR-A-Matrix : A Matrix Themed Car Rental System

Hello Dear Users,<br>
Hope you all enjoyed your journey to CAR-A-MATRIX, a Matrix themed car rental system. 

##Assumptions and Special Features
Every user has a unique user_id.<br>
The condition of the car decreases by 10 after every rent. However, under special circumstances, a manager can update the goodness_index if needed using the update function of the user.<br>
Payment of rent and fines is an offline transaction. The app informs the user regarding the payment which is to be done then and there to the local manager.<br>
The user pays the rent while initially renting the car and pays the fine while returning the car.<br>
The goodness index(customer record) helps determine how many cars a person can rent.<br>
The user can always rent 1 car no matter what his goodness index is since the minimum value of goodness_index attainable is 10 .<br>

##Working of the App
When the app is started, the user has three options. The existing users can login, new users can register and if wanted, they can exit the application.<br>
Registration is a simple process wherein the app requires the user's name, prompts to create a used id, password and enables the selection of the role of the user.<br>
Login of the user demands the used id and password and based on the database of the users, they are prompted to their respective login pages.<br>
A normal user and employee have the same options except for the fact that employees get a 15 percent discount on renting but are imposed double the fine for every day delayed. The fine is 25 percent of the rental price of the car for customers and 50 percent of the rental price of the car for employees.<br>
The manager has much more functionality in the sense that he can add, update and delete users as well as cars.<br>
Regarding the user, we store his name, id ,password and goodness_value(as a measure for customer record). Car-A-Matrix assumes that goodness_value changes only on the basis of delay in returning and leaves the goodness_value change based on the condition of the car at the discretion of the manager.<br>
Regarding the car, we store its name/model(assuming only 1 car of each model), its condition (on a scale from 0 to 100, 35 being the minimum for rentable) and whether it is currently rented or not. Also, after each rent, the condition of the car decreases by 10. So below 35, the only way the car can be rented again is if it is serviced at which the manager updates the condition of the car making it rentable again. Regarding the rented condition, 0 indicated the car is currently not being rented by anyone and 1 represents that the car is currently under rent.<br>
Now, the information regarding the users is stored in a common all users database as well as a separate database for different types of users. In addition, there are also databases for all the cars and cars that are currently being rented.<br>
Also, a normal customer can rent a car for 5 days and an employee for 7 days. These are the minimum renting periods and all the renting periods can only be multiples of these where you simply need to rent them again.<br>
Well, that's that. Hope you can enjoy the experience of a thrilling car renting adventure through the CAR-A-MATRIX.
