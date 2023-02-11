# Intellec8

I bought this Intellec 8/80 on a fleamarked outside Stockholm 30 years ago for the equivalent of ten euros. It has been sitting on a shelf since then and now I got the inspiration to fix it. Before doing anything with this machines I dumed the [firmware](https://github.com/MattisLind/Intellec8/tree/main/EPROMImages) of the EPROMs. 16 1702 EPROM chips. Each of them containing 256 bytes of non-volatile storage. Then I dismantled the entire machine in to pieces and cleaned some 40 years of dust from it. Meanwhile I took quite a lot of photos of the various parts and puth in the [Pictures folder](https://github.com/MattisLind/Intellec8/tree/main/Pictures). 

![Front panel](https://raw.githubusercontent.com/MattisLind/Intellec8/main/Pictures/Frontpanel.jpg)

The first thing to check were the PSU. The Intellec 8 has three PSU assemblies. One provides +5V, One provide +/- 12V and the one provide -9V and AC for the programming voltage.

![5V PSU](https://raw.githubusercontent.com/MattisLind/Intellec8/main/Pictures/5VPSU.JPG)

The first thing I tested was the little crowbar addon board. It tripped at almost 9V, a bit to much in my taste, but it was possible to adjust it down to 5.7V. There didn't seemed to be any problems with that other than it was not set correctly.

Then I started working with the PSUs. All off them worked fine except for the +5V PSU that didn't regulate well at all. I had to turn off the crowbare not to make it trip every time. Evverything measured fine, capacitors, carbon composite resistors, forward drop over semiconductor PN-junctions. But it didn't regulate well. Tried to replace the LM723 regulator IC with a NOS IC. But no difference. Then I looked more on the power transistor that acted as a driver for the output stage of the regulator. It was very leaky. With a new power transistor in place the PSU worked fine.

I installed the Front panel controller, CPU and the three memory boards in the backplane and attached the flat cables from the front panel to the front panel controller board and turne the power switch on. There were some kind of activity on the front panel. I could examine and deposit into memory, but RUN mode behaved odd. I wasn't able to single step the CPU but the RUN light could come on. But in RUN mode there were no activity on the FETCH indicator. Strange.

I checked all LEDs on the panel and they seemed to work find as did the switches. To trace problems further I needed to meausure on the front panel controller board. That was quite tricky with the board installed in the backplane. I needed an extender card. So I sat down one Saturday and designed one.

![Extender board](https://i.imgur.com/qulnBwCl.jpg)

I also inclued test point so it wouuld be easier to attach a logic analyzer if that turned out to be necessary. The more test points the better. And a lot of ground points to be able to attache the ground probes of the LA.

A few weeks later the boards arrived and so did the connector. I choosen a wire-wrap connector which i bent the legs a bit on to make a sturdy connection between the board and the connector.

![Extender baord end front panel board in the chassis](https://i.imgur.com/Fs8Oeyml.jpg)

Now I hade the possibiliy to probe around on the board. The FETCH cycle signal toggled all the time but still the LED was dark. The signal went through a 7417 OC buffer, A3. It turned out that it was allways high on the output. A low will cause the LED to be lit. A high will cause it to be turned off. Removed it and tested in my Retro Chip Tester and, yes, it tested bad. A new (date code 1971), tested, 7417 was installed and yes the front panel was a lot happier.

I could enter a short loop at address 0 that was looping back to itself and also single step this little program. Nice!

But when checking the memory at 3800h where the monitor was supposed be located were very strange and did not match the content of the previouslt dumped EPROMs. Pulled out the EPROM board from the backplane and immediatelty saw something that made me suspicous. Two DIP-swicthes. I have had problmes with DIP-switches in the past. And sure enough, closed switches read open-circuit on the meter. Tried to exercise the switches. Tried deoxit, which made it worse. In the end I had to replace them and then with new swicthes in place the memory at 3800h was accessible. I could even start the monitor and saw the LED indicate I/O acces which was likely to be the monitor polling the UART for incoming character.

Now I just have create a current loop adapter and test the I/O card.
