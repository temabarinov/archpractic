#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/Session.h>
#include <Wt/Dbo/backend/Postgres.h>
#include <iostream>
#include <memory>
#include <string>

class shop {
public:
  int id = 0;
  std::string name{};

  template <class Action> void persist(Action &a) {}
};

int main() {
  std::string connectionString = "host=localhost"
                                 " port=5432"
                                 " dbname=wttest"
                                 " user=postgres"
                                 " password=Zxc200709?";
  auto postgres =
      std::make_unique<Wt::Dbo::backend::Postgres>(connectionString);
  Wt::Dbo::Session session;
  session.setConnection(std::move(postgres));
  session.mapClass<shop>("shop");

  return 0;
}