# Quorismart AI Group Project
## Make Quoridor Smart Again

## Running the project
* garry can you complete this section?

## Cloning the repo
`git clone git@cs-devel.potsdam.edu:cis421/teamQuorismart`

### Adding inbound IP address to AWS to connect to database via sqlWorkbench or 
1. Determine your public IP address (a quick google search: "what is my ip")
2. In AWS, Go to DB instance --> Security And Network --> Click on Security groups hyperlink
3. Click the inbound tab at the bottom
4. Click "Edit" select the type to be "MYSQL/Aurora", Protocol "TCP", Port range "3306", Add your IP "XXX.XXX.XX.XXX" with "/32" appended at the end
5. Done!

### Connecting to the database via SQL workbench
1. Open sqlWorkbench
2. Database --> Connect to database
3. Hostname: quordb.c42xpoddmdpg.us-west-2.rds.amazonaws.com
4. Port: 3306
5. Password will be asked for on the next screen: Vfer498\u&U{\5F2. Changed to root1234
6. Celebrate, you're connected!

See more here: http://docs.aws.amazon.com/AmazonRDS/latest/UserGuide/CHAP_GettingStarted.CreatingConnecting.MySQL.html

### Connecting to the database via terminal (still not complete, use workbench)
1. Install mySQL here: http://dev.mysql.com/doc/refman/5.7/en/installing.html
Download page found here: http://dev.mysql.com/downloads/mysql/
2. After installing mySQL, open the terminal and enter `mysql -h quordb.c42xpoddmdpg.us-west-2.rds.amazonaws.com:3306 -P 3306 -u quordb -p`. You will be prompted to enter the password, `Vfer498\u&U{\5F2`

## Team Members
- Garry Griggs - C++ Master
- Matt Coupal - C++ Apprentice \(^.^)/
- Jesse Peplinski - Database Guru
