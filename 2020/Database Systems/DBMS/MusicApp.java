import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Scanner;
import java.sql.Date;

public class MusicApp {
	public static void main(String[] args) {
		String driver = "org.mariadb.jdbc.Driver";
		Connection con;
	    PreparedStatement pstmt = null;
	    ResultSet rs = null;
	    
	    Scanner sc = new Scanner(System.in);
	    int firstMenu, secondMenu;
	    
	    try {
	    	Class.forName(driver);
	    	con = DriverManager.getConnection("jdbc:mariadb://localhost:3306/music", "root", "gusah");
	    	if(con != null) {
	    		System.out.println("DB 접속 성공");
	    		Statement stmt = con.createStatement();
	    		while(true) {
	    			System.out.println("----- Wellcome to My Music APP -----");
	    			System.out.println("1. Manager Menu\n2. Subscriber Menu\n0. Exit");
	    			System.out.print(">> ");
	    			firstMenu = sc.nextInt();
	    		
	    			if(firstMenu == 1) {
	    				System.out.print("Enter your nick name: ");
	    				String nickName = sc.next();
	    				pstmt = con.prepareStatement("SELECT Name, Ssn FROM music.MANAGER WHERE NickName = ?");
	    				pstmt.setString(1, nickName);
	    				rs = pstmt.executeQuery();
	   
	    				if(rs.next()) {
	    					System.out.println("\n***** Wellcome " + rs.getString("Name") + " *****");
	    					String mgrSsn = rs.getString("Ssn");
	    					while(true) {
	    						System.out.println("----- Manager Menu -----");
	    						System.out.println("1. Add Songs\n2. Delete Songs\n3. Add Artist\n4. Delete Subscribers\n5. Edit Manager Information\n6. Show All Managing\n0. Return to Previous Menu");
	    						System.out.print(">> ");
	    						secondMenu = sc.nextInt();
	    						sc.nextLine();
	    						if(secondMenu == 1) {
	    							int songNum;
	    							String title, lyrics, singer, writer, composer;
	    							int time;
	    							rs = stmt.executeQuery("SELECT MAX(Number) FROM SONG");
	    							rs.next();
	    							int current = rs.getInt("MAX(Number)");
	    							System.out.print("How many songs will you add? ");
	    							songNum = sc.nextInt();
	    							for(int i = 1; i <= songNum; i++) {
	    								System.out.print("Enter " + i + "th song name: ");
	    								title = sc.next();
	    								sc.nextLine();
	    								System.out.print("Enter " + i + "th song\'s lyrics: ");
	    								lyrics = sc.next();
	    								sc.nextLine();
	    								System.out.print("Enter " + i + "th song\'s play time: ");
	    								time = sc.nextInt();
	    								sc.nextLine();
	    								System.out.print("Enter " + i + "th song\'s singer: ");
	    								singer = sc.next();
	    								sc.nextLine();
	    								System.out.print("Enter " + i + "th song\'s writer: ");
	    								writer = sc.next();
	    								sc.nextLine();
	    								System.out.print("Enter " + i + "th song\'s composer: ");
	    								composer = sc.next();
	    								sc.nextLine();
	    								
	    								int error = 0;
	    								pstmt = con.prepareStatement("select Number from ARTIST where Name = ?");
	    								pstmt.setString(1, singer);
	    								rs = pstmt.executeQuery();
	    								int singerNum = 0;
	    								if(rs.next()) {
	    									singerNum = rs.getInt("Number");
	    								} else {
	    									System.out.println("No such artist!!!");
	    									error = 1;
	    								}
	    									
	    								
	    								pstmt = con.prepareStatement("select Number from ARTIST where Name = ?");
	    								pstmt.setString(1, writer);
	    								rs = pstmt.executeQuery();
	    								int writerNum = 0;
	    								if(rs.next()) {
	    									writerNum = rs.getInt("Number");
	    								} else {
	    									System.out.println("No such artist!!!");
	    									error = 1;
	    								}
	    								
	    								pstmt = con.prepareStatement("select Number from ARTIST where Name = ?");
	    								pstmt.setString(1, composer);
	    								rs = pstmt.executeQuery();
	    								int composerNum = 0;
	    								if(rs.next()) {
	    									composerNum = rs.getInt("Number");
	    								} else {
	    									System.out.println("No such artist!!!");
	    									error = 1;
	    								}
//	    								
//	    								pstmt = con.prepareStatement("insert into SING values ()");
	    								
	    								if(error == 1) {
	    									System.out.println("Add song fail!!!");
	    								} else {
	    									pstmt = con.prepareStatement("insert into SONG values (?, ?, ?, ?, 0, ?)");
		    								pstmt.setString(1, title);
		    								pstmt.setInt(2, current + i);
		    								pstmt.setString(3, lyrics);
		    								pstmt.setInt(4, time);
		    								pstmt.setString(5, mgrSsn);
		    								rs = pstmt.executeQuery();
		    								
		    								pstmt = con.prepareStatement("insert into SING values(?, ?)");
		    								pstmt.setInt(1, current + i);
		    								pstmt.setInt(2, singerNum);
		    								rs = pstmt.executeQuery();
		    								
		    								pstmt = con.prepareStatement("insert into WRITE_SONG values(?, ?)");
		    								pstmt.setInt(1, current + i);
		    								pstmt.setInt(2, writerNum);
		    								rs = pstmt.executeQuery();
		    								
		    								pstmt = con.prepareStatement("insert into COMPOSE values(?, ?)");
		    								pstmt.setInt(1, current + i);
		    								pstmt.setInt(2, composerNum);
		    								rs = pstmt.executeQuery();
		    								
		    								System.out.println("Add song success!");
	    								}
	    							}
	    							
	    						} else if(secondMenu == 2) {
	    							System.out.print("How many songs will you delete? ");
	    							int songNum = sc.nextInt();
	    							sc.nextLine();
	    							for(int i = 1; i <= songNum; i++) {
	    								System.out.print("Enter " + i + "th song number: ");
	    								int number = sc.nextInt();
	    								sc.nextLine();
	    								
	    								pstmt = con.prepareStatement("select Number from SONG as s, MANAGER as m where s.MgrSsn = ?");
	    								pstmt.setString(1, mgrSsn);
	    								rs = pstmt.executeQuery();
	    								
	    								int error = 1;
	    								
	    								while(rs.next()) {
	    									if(rs.getInt("Number") == number) {
	    										error = 0;
	    										break;
	    									}
	    									error = 1;
	    								}
	    								
	    								if(error == 0) {
	    									PreparedStatement tmpPstmt = con.prepareStatement("delete from SING where SNum = ?");
	    									tmpPstmt.setInt(1, number);
	    									tmpPstmt.executeQuery();
	    									
	    									tmpPstmt = con.prepareStatement("delete from COMPOSE where SNum = ?");
	    									tmpPstmt.setInt(1, number);
	    									tmpPstmt.executeQuery();
	    									
	    									tmpPstmt = con.prepareStatement("delete from WRITE_SONG where SNum = ?");
	    									tmpPstmt.setInt(1, number);
	    									tmpPstmt.executeQuery();
	    									
	    									pstmt = con.prepareStatement("delete from SONG where Number = ?");
	    									pstmt.setInt(1, number);
	    									rs = pstmt.executeQuery();
	    									System.out.println("Delete success!");
	    								} else {
	    									System.out.println("No such song or no permition");
	    								}
	    							}
//	    							System.out.println(songNum + " song(s) delete success!");
	    						} else if(secondMenu == 3) {
	    							System.out.print("Enter artist name: ");
	    							String aName = sc.next();
	    							sc.nextLine();
	    							System.out.print("Enter artist debut(ex. 1900-03-28 \\if you don\'t know, enter 0): ");
	    							String debut = sc.next();
	    							sc.nextLine();
	    							
	    							//TODO: check if the artist exists
	    							
	    							pstmt = con.prepareStatement("select max(Number) from ARTIST");
	    							rs = pstmt.executeQuery();
	    							rs.next();
	    							int current = rs.getInt("max(Number)");
	    							
	    							if(debut.equals("0")) {
	    								pstmt = con.prepareStatement("insert into ARTIST(Name, Number, MgrSsn) values(?, ?, ?)");
	    								pstmt.setString(1, aName);
	    								pstmt.setInt(2, current + 1);
	    								pstmt.setString(3, mgrSsn);
	    								rs = pstmt.executeQuery();
	    							} else {
	    								Date d = Date.valueOf(debut);
	    								pstmt = con.prepareStatement("insert into ARTIST values(?, ?, ?, ?)");
	    								pstmt.setString(1, aName);
	    								pstmt.setInt(2, current + 1);
	    								pstmt.setDate(3, d);
	    								pstmt.setString(4, mgrSsn);
	    								rs = pstmt.executeQuery();
	    							}
	    							System.out.println("Add artist success!");
	    							
	    						} else if(secondMenu == 4) {
	    							System.out.print("Enter nick name of subscriber: ");
	    							String deleteSub = sc.next();
	    							sc.nextLine();
	    							
	    							pstmt = con.prepareStatement("select s.NickName from SUBSCRIBER as s, MANAGER as m where s.MgrSsn = ?");
    								pstmt.setString(1, mgrSsn);
    								rs = pstmt.executeQuery();
    								
    								if(rs.next()) {
    									pstmt = con.prepareStatement("delete from SUBSCRIBER where NickName = ?");
    									pstmt.setString(1, deleteSub);
    									rs = pstmt.executeQuery();
    									System.out.println("Delete success!");
    								} else {
    									System.out.println("No such subscriber or no permition");
    								}
	    						} else if(secondMenu == 5) {
	    							System.out.println("Which one will you edit?");
	    							System.out.println("1. Name\n2. NickName");
	    							System.out.print(">> ");
	    							int edit = sc.nextInt();
	    							sc.nextLine();
	    							if(edit == 1) {
	    								System.out.print("Enter new name: ");
	    								String newName = sc.next();
	    								sc.nextLine();
	    								pstmt = con.prepareStatement("update MANAGER set Name = ? where Ssn = ?");
	    								pstmt.setString(1, newName);
	    								pstmt.setString(2, mgrSsn);
	    								rs = pstmt.executeQuery();
	    							} else if(edit == 2) {
	    								System.out.print("Enter new nick name: ");
	    								String newNickName = sc.next();
	    								sc.nextLine();
	    								pstmt = con.prepareStatement("update MANAGER set NickName = ? where Ssn = ?");
	    								pstmt.setString(1, newNickName);
	    								pstmt.setString(2, mgrSsn);
	    								rs = pstmt.executeQuery();
	    							} else {
	    								System.out.println("Wrong Input!!!");
	    							}
	    						} else if(secondMenu == 6) {
//	    							System.out.println("All Managing");
	    							pstmt = con.prepareStatement("select s.Name, s.NickName from music.MANAGER as m, music.SUBSCRIBER as s where m.Ssn = ? and m.Ssn = s.MgrSsn");
	    							pstmt.setString(1, mgrSsn);
	    							rs = pstmt.executeQuery();
	    							if(rs.next()) {
	    								System.out.println("Subscriber:");
	    								do{
	    									System.out.println("Name: " + rs.getString("Name") + ", Nick Name: [" + rs.getString("NickName") + "]");
	    								} while(rs.next());
	    							} else {
	    								System.out.println("No subscriber managing");
	    							}
	    							
	    							pstmt = con.prepareStatement("select song.Title, song.Number from music.MANAGER as m, music.SONG as song where m.Ssn = ? and m.Ssn = song.MgrSsn");
	    							pstmt.setString(1, mgrSsn);
	    							rs = pstmt.executeQuery();
	    							if(rs.next()) {
	    								System.out.println("Song:");
	    								do{
	    									System.out.println("Title: \"" + rs.getString("Title") + "\", Number: " + rs.getString("Number"));
	    								} while(rs.next());
	    							} else {
	    								System.out.println("No song managing");
	    							}
	    						} else if(secondMenu == 0) {
	    							break;	
	    						} else {
	    							System.out.println("Wrong Input!!!\n");
	    						}
	    					}
	    				} else {
	    					System.out.println("Invalid nick name!!!");
	    				}
	    			} else if(firstMenu == 2) {
	    				System.out.print("Enter your nick name: ");
	    				String nickName = sc.next();
	    				pstmt = con.prepareStatement("SELECT Name, Ssn FROM music.SUBSCRIBER WHERE NickName = ?");
	    				pstmt.setString(1, nickName);
	    				rs = pstmt.executeQuery();
	    				
	    				if(rs.next()) {
	    					System.out.println("\n***** Wellcome " + rs.getString("Name") + " *****");
	    					String subSsn = rs.getString("Ssn");
	    					
	    					while(true) {
		    					System.out.println("----- Subscriber Menu -----");
		    					System.out.println("1. Make New Playlist\n2. Delete Playlist\n3. Edit Playlist\n4. Play songs\n5. Edit Subsriber Information\n6. Search Song\n0. Return to Previous Menu");
		    					System.out.print(">> ");
		    					secondMenu = sc.nextInt();
		    					sc.nextLine();
		    					if(secondMenu == 1) {
		    						rs = stmt.executeQuery("SELECT MAX(Number) FROM PLAYLIST");
	    							rs.next();
	    							int current = rs.getInt("MAX(Number)");
	    							
		    						System.out.print("Enter new playlist name: ");
		    						String pName = sc.next();
		    						sc.nextLine();
		    						
		    						pstmt = con.prepareStatement("select Number from PLAYLIST where Name = ?");
		    						pstmt.setString(1, pName);
		    						rs = pstmt.executeQuery();
		    						
		    						if(rs.next()) {
		    							System.out.println("Name Already exists.");
		    						} else {
		    							pstmt = con.prepareStatement("insert into PLAYLIST values (?, ?, ?)");
		    							pstmt.setString(1, pName);
		    							pstmt.setInt(2, current + 1);
		    							pstmt.setString(3, subSsn);
		    							rs = pstmt.executeQuery();
		    							System.out.println("Add playlist success!");
		    						}
		    						
		    					} else if(secondMenu == 2) {
		    						System.out.print("Enter "
		    								+ "playlist name: ");
		    						String pName = sc.next();
		    						sc.nextLine();
		    						
		    						pstmt = con.prepareStatement("select Number from PLAYLIST where Name = ?");
		    						pstmt.setString(1, pName);
		    						rs = pstmt.executeQuery();
		    						
		    						if(rs.next()) {
		    							pstmt = con.prepareStatement("delete from PLAYLIST where Name = ?");
		    							pstmt.setString(1, pName);
		    							rs = pstmt.executeQuery();
		    							System.out.println("Delete playlist success!");
		    						} else {
		    							System.out.println("No such playlist!!!");
		    						}
		    					} else if(secondMenu == 3) {
		    						System.out.print("Enter play list name: ");
		    						String pName = sc.next();
		    						sc.nextLine();
		    						
		    						pstmt = con.prepareStatement("select Number from PLAYLIST where Name = ?");
		    						pstmt.setString(1, pName);
		    						rs = pstmt.executeQuery();
		    						
		    						if(rs.next()) {
		    							int pNum = rs.getInt("Number");
		    							System.out.println("1. Edit playlist name\n2. Add songs\n3. Delete songs");
		    							int pMenu = sc.nextInt();
		    							sc.nextLine();
		    							
		    							if(pMenu == 1) {
		    								System.out.print("Enter new name: ");
		    								String newName = sc.next();
		    								sc.nextLine();
		    								
		    								pstmt = con.prepareStatement("update PLAYLIST set Name = ? where Number = ?");
		    								pstmt.setString(1, newName);
		    								pstmt.setInt(2, pNum);
		    								pstmt.executeQuery();
		    								
		    								System.out.println("Update name success");
		    							} else if(pMenu == 2) {
		    								System.out.print("Enter song name: ");
		    								String songName = sc.next();
		    								sc.nextLine();
		    								
		    								pstmt = con.prepareStatement("select Number from SONG where Title = ?");
		    								pstmt.setString(1, songName);
		    								rs = pstmt.executeQuery();
		    								rs.next();
		    								int songNum = rs.getInt("Number");
		    								
		    								pstmt = con.prepareStatement("insert into CONTAIN values(?, ?, ?)");
		    								pstmt.setInt(1, songNum);
		    								pstmt.setInt(2, pNum);
		    								pstmt.setString(3, subSsn);
		    								rs = pstmt.executeQuery();
		    								
		    								System.out.println("Add song success!");
		    							} else if(pMenu == 3) {
		    								System.out.print("Enter song name: ");
		    								String songName = sc.next();
		    								sc.nextLine();
		    								
		    								pstmt = con.prepareStatement("select Number from SONG where Title = ?");
		    								pstmt.setString(1, songName);
		    								rs = pstmt.executeQuery();
		    								if(rs.next()) {
		    									int songNum = rs.getInt("Number");
		    									
		    									pstmt = con.prepareStatement("delete from CONTAIN where SNum = ?");
		    									pstmt.setInt(1, songNum);
		    									pstmt.executeQuery();
		    								} else {
		    									System.out.println("No such song");
		    								}
		    							} else {
		    								
		    							}
		    						} else {
		    							System.out.println("No such play list!!!");
		    						}
		    						
		    						
		    					} else if(secondMenu == 4) {
		    						pstmt = con.prepareStatement("select Name from PLAYLIST");
		    						rs = pstmt.executeQuery();
		    						while(rs.next()) {
		    							System.out.println("Playlist name : " + rs.getString("Name"));
		    						}
		    						System.out.print("Enter play list name: ");
		    						String pName = sc.next();
		    						sc.nextLine();
		    						
		    						pstmt = con.prepareStatement("select song.Title, song.PlayTime, a.Name, song.PlayCount, song.Number from music.PLAYLIST as p, music.SING as sing, music.SONG as song, music.ARTIST as a, music.CONTAIN as c where c.PNum = p.`Number` and c.SNum = song.Number and song.Number = sing.SNum and sing.ArtNum = a.`Number` and p.name = ?");
		    						pstmt.setString(1, pName);
		    						rs = pstmt.executeQuery();
		    						int count = 0;
		    						System.out.println("Play " + pName);
		    						
		    						ResultSet tmpRs;
		    						PreparedStatement tmpPstmt;
		    						
		    						while(rs.next()) {
		    							count++;
		    							System.out.println("(" + count + ") Title: " + rs.getString("song.Title") + ", Singer: " + rs.getString("a.Name"));
		    							tmpPstmt = con.prepareStatement("update SONG set PlayCount = ? where Number = ?");
		    							tmpPstmt.setInt(1, rs.getInt("song.PlayCount") + 1);
		    							tmpPstmt.setInt(2, rs.getInt("song.Number"));
		    							tmpRs = tmpPstmt.executeQuery();
		    						}
		    						
		    						if(count == 0) {
		    							System.out.println("Empty playlist");
		    						} else {
		    							pstmt = con.prepareStatement("select sum(song.PlayTime), count(song.Number) from music.PLAYLIST as p, music.SING as sing, music.SONG as song, music.ARTIST as a, music.CONTAIN as c where c.PNum = p.`Number` and c.SNum = song.Number and song.Number = sing.SNum and sing.ArtNum = a.`Number` and p.name = ?");
			    						pstmt.setString(1, pName);
			    						rs = pstmt.executeQuery();
			    						rs.next();
			    						
			    						System.out.println("The number of song: " + rs.getInt("count(song.Number)"));
			    						System.out.println("Total time: " + rs.getInt("sum(song.PlayTime)") / 60 + "minutes " + rs.getInt("sum(song.PlayTime)") % 60 + "seconds");
			    						
		    						}
		    						
		    					} else if(secondMenu == 5) {
		    						System.out.println("Which one will you edit?");
	    							System.out.println("1. Name\n2. NickName");
	    							System.out.print(">> ");
	    							int edit = sc.nextInt();
	    							sc.nextLine();
	    							
	    							if(edit == 1) {
	    								System.out.print("Enter new name: ");
	    								String newName = sc.next();
	    								sc.nextLine();
	    								pstmt = con.prepareStatement("update SUBSCRIBER set Name = ? where Ssn = ?");
	    								pstmt.setString(1, newName);
	    								pstmt.setString(2, subSsn);
	    								rs = pstmt.executeQuery();
	    							} else if(edit == 2) {
	    								System.out.print("Enter new nick name: ");
	    								String newNickName = sc.next();
	    								sc.nextLine();
	    								pstmt = con.prepareStatement("update SUBSCRIBER set NickName = ? where Ssn = ?");
	    								pstmt.setString(1, newNickName);
	    								pstmt.setString(2, subSsn);
	    								rs = pstmt.executeQuery();
	    							} else {
	    								System.out.println("Wrong Input!!!");
	    							}
		    					} else if(secondMenu == 6) {
		    						System.out.println("1. Search with title\n2. Search with artist\n3. Search with lyrics");
		    						System.out.print(">> ");
		    						int tmp = sc.nextInt();
		    						sc.nextLine();
		    						
		    						if(tmp == 1) {
		    							System.out.print("Enter title: ");
		    							String title = sc.next();
		    							sc.nextLine();
		    							pstmt = con.prepareStatement("select song.Title, a.Name from SONG as song, SING as sing, ARTIST as a where song.Title like ? and song.Number = sing.SNum and sing.ArtNum = a.Number order by PlayCount DESC");
		    							pstmt.setString(1, "%" + title + "%");
		    							rs = pstmt.executeQuery();
		    							
		    							if(rs.next()) {
		    								do {
		    									System.out.println("Title: " + rs.getString("song.Title") + ", Singer: " + rs.getString("a.Name"));
		    								} while (rs.next());
		    							} else {
		    								System.out.println("No result!");
		    							}
		    						} else if(tmp == 2) {
		    							System.out.print("Enter artist name: ");
		    							String aName = sc.next();
		    							sc.nextLine();
		    							pstmt = con.prepareStatement("select song.Title, a.Name from SONG as song, SING as sing, ARTIST as a where a.Name like ? and a.Number = sing.ArtNum and sing.SNum = song.Number");
		    							pstmt.setString(1, "%" + aName + "%");
		    							rs = pstmt.executeQuery();
		    							
		    							if(rs.next()) {
		    								do {
		    									System.out.println("Title: " + rs.getString("song.Title") + ", Singer: " + rs.getString("a.Name"));
		    								} while (rs.next());
		    							} else {
		    								System.out.println("No result!");
		    							}
		    						} else if(tmp == 3) {
		    							System.out.print("Enter lyrics name: ");
		    							String lyrics = sc.next();
		    							sc.nextLine();
		    							pstmt = con.prepareStatement("select song.Title, a.Name from SONG as song, SING as sing, ARTIST as a where song.Lyrics like ? and a.Number = sing.ArtNum and sing.SNum = song.Number");
		    							pstmt.setString(1, "%" + lyrics + "%");
		    							rs = pstmt.executeQuery();
		    							
		    							if(rs.next()) {
		    								do {
		    									System.out.println("Title: " + rs.getString("song.Title") + ", Singer: " + rs.getString("a.Name"));
		    								} while (rs.next());
		    							} else {
		    								System.out.println("No result!");
		    							}
		    						} else {
		    							System.out.println("Wrong Input!!!");
		    						}
		    					} else if(secondMenu == 0) {
		    						break;
		    					} else {
		    						System.out.println("Wrong Input!!!\n");
		    					}
		    				}
	    				} else {
	    					System.out.println("Invalid nick name!!!");
	    				}
	    			} else if(firstMenu == 0) {
	    				System.out.println("Bye!");
	    				break;
	    			} else {
	    				System.out.println("Wrong Input!!!\n");
	    			}
	    		}
	    		stmt.close();
	    	}
	    		
	    	con.close();
	    	pstmt.close();
	    	rs.close();
	    } catch (ClassNotFoundException e) {
	    	System.out.println("드라이버 로드 실패");
	    } catch (SQLException e) {
	    	System.out.println("DB 접속 실패");
	    	e.printStackTrace();
	    }
		
	}
}

//TODO: register new account
