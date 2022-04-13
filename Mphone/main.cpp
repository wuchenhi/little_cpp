/*
 * @Author: 光城
 * @Date: 2021-05-11 08:07:55
 * @LastEditors: 光城
 * @LastEditTime: 2021-05-11 09:33:52
 * @Description:
 * @FilePath: \code\kg\phone\main.cpp
 */
#include "phone.h"

int main() {
  int op, ch;
  PhoneManageSystem pms;
  do {
    printf("-------Welcome--------\n");
    printf("1.Create\n2.Display\n3.Delete\n4.Search\n5.GetSize\n");
    printf("Enter your choice:");
    scanf("%d", &ch);
    switch (ch) {
      case 1:
        pms.create();
        break;
      case 2:
        pms.display();
        break;
      case 3:
        pms.del();
        break;
      case 4:
        pms.search();
        break;
      case 5:
        cout << "size=" << pms.getSize() << endl;
        break;
    }
    printf("Do you want to quit ? 1 for no / 0 for yes:");
    scanf("%d", &op);
  } while (op);
  return 0;
}