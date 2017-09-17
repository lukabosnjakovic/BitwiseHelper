# Bitwise Helper
---
Are you embedded programmer that's using open source tools? You code for microcontrollers and you know what is bitmask?
Than you know how confusing and difficult can be setting bits you must set if you want to use some microcontroller's peripherial.

### Idea
The idea behind application is that you can have on one place all important microcontroller's registers used to enable peripherals inside microcontroller and make mask that enable what you want.

### Usage 
You simply open bitmask template (register) and you click on bit you want to set (1) or clear (0).
After you are done with setting bits you can easily copy bitmask representation as decimal or hexadecimal (or even binary) number and paste it in your code.
You can open bitmask template (register) from tree on the left side or with open button in application's menu.

### Making bitmask template (register)
When you want to make new bitmask template which is microcontroller's register representation click "New" button in application's ribbon.
You will get new bitmask with 32 bits. That is application's maximum (sorry 64-bit guys).
As common resolutions are 8, 16 and 32 you can select one of those resolutions with slider in ribbon.
Bits names you can change by clicking check box "Enable" in ribbon. After changing names uncheck check box to continue with saving bitmask template.
As microcontrollers and microprocessors can have different bit orientation you can change where which importance has first bit on left. So it can be Most Significant bit (MSB) or Least Significant bit (LSB).

### Technical info
Application is written in C++ with MFC library so it is for Windows only.
It was a part of my education as project for my college class NWP (Napredno Windows programiranje in English: Addvanced Windows programming).