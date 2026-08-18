#include <iostream>
#include <pqxx/pqxx>
#include <string>
class libpqxxx {
private:
  pqxx::connection conn{};

public:
  libpqxxx()
      : conn("host=localhost port=5432 dbname=libtest user=postgres "
             "password=Zxc200709?") {}
  void createdb() {
    pqxx::work tx{conn};
    tx.exec("create table if not exists clients(id serial primary key, name "
            "varchar(20) not null, lastname varchar(20) not null,email "
            "varchar(30) not null); create table if not exists numbers(id "
            "integer references clients(id),number varchar(30));");

    tx.commit();
  }
  void addclientWithNumber(std::string name_, std::string lastname_,
                           std::string email_, std::string number_) {
    pqxx::work tx{conn};
    tx.exec("insert into clients(name,lastname,email) values('" +
            tx.esc(name_) + "','" + tx.esc(lastname_) + "','" + tx.esc(email_) +
            "'); insert into numbers values((select id from clients where name='" +
            tx.esc(name_) + "' and lastname='" + tx.esc(lastname_) +
            "' limit 1),'" + tx.esc(number_) +
            "');");
    tx.commit();
  }
  void addNumberforUser(std::string number, std::string name_,
                        std::string lastname) {
    pqxx::work tx{conn};
    tx.exec("insert into numbers values((select id from clients where name='" +
            tx.esc(name_) + "' and lastname='" + tx.esc(lastname) +
            "' limit 1),'" + tx.esc(number) + "');");
    tx.commit();
  }
  void updateClientInfo(std::string name, std::string lastname, std::string newemail){
    pqxx::work tx{conn};
    tx.exec("update clients set email='" + tx.esc(newemail) + "' where name='"+ tx.esc(name) + "' and lastname='" + tx.esc(lastname) + "';");
    tx.commit();



  }

  void deletenumber(std::string number){
    pqxx::work tx{conn};
    tx.exec("delete from numbers where number='" + tx.esc(number) + "';");
    tx.commit();
  }
  void deleteUser(std::string name, std::string lastname){
    pqxx::work tx{conn};
    tx.exec("delete from numbers where id=(select id from clients where name='" + tx.esc(name) + "' and lastname='" + tx.esc(lastname) + "');" 
            "delete from clients where name='" + tx.esc(name) + "' and lastname='" + tx.esc(lastname) + "';");
    tx.commit();
  }

  void findClientName(std::string name){
    pqxx::work tx{conn};
    for (auto[id,name,lastname,email] : tx.query<int,std::string,std::string,std::string>("select id,name,lastname,email from clients where name='" + tx.esc(name) + "';")){
        std::cout<<id << " " << name << " " << lastname << " " << email<<std::endl;
    }
    tx.commit();
    

  }
  void findClientLastname(std::string lastname){
    pqxx::work tx{conn};
    for (auto[id,name,lastname,email] : tx.query<int,std::string,std::string,std::string>("select id,name,lastname,email from clients where lastname='" + tx.esc(lastname) + "';")){
        std::cout<<id << " " << name << " " << lastname << " " << email<<std::endl;
    }
    tx.commit();



  }
  void findClientemail(std::string email){
    pqxx::work tx{conn};
    for (auto[id,name,lastname,email] : tx.query<int,std::string,std::string,std::string>("select id,name,lastname,email from clients where email='" + tx.esc(email) + "';")){
        std::cout<<id << " " << name << " " << lastname << " " << email<<std::endl;
    }
    tx.commit();



  }
};
int main() {
  try {
    libpqxxx obj;
    obj.createdb();
    obj.addclientWithNumber("ivan", "ivanov", "ivan@gmail.com", "89999999990");
    //obj.addNumberforUser("8923939234", "ivan", "ivanov");
    //obj.deletenumber("8923939234");
    
    
    obj.findClientName("ivan");
    obj.findClientLastname("ivanov");
    obj.findClientemail("ivan@gmail.com");
  } catch (const pqxx::sql_error &err) {
    std::cout << err.what() << std::endl;
  }

  return 0;
}