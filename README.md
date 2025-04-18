# Ambient Beer Room Thermometer

I brew beer for a hobby and want to know which room in my house I can use as a
fermentation room. I built this simple thing so that I can remotely record
historical data for different rooms.

Historical data is important because (for example) the furnace room can swing
quite a bit throughout the day. It gets cold at night in the winter (I live in
Canada), then spikes in the morning to get the house warmed up, then gradually
drops once it's in maintenance mode for the day. At least I think so!

Wandering in and spot checking wouldn't suffice: I wanted a graph that spans
nights, weekends, etc. Yeast never sleeps!

## Hardware

The hardware used for this project is a NodeMCU ESP8266 Development board for
the guts, and an AHT21 temperature/humidity sensor for the useful parts.

The sensor is wired in as follows:
| AHT21 | NodeMCU    |
| ----- | ---------- |
| VCC   | 3.3V       |
| GND   | GND        |
| SDA   | D2 (GPIO4) |
| SCL   | D1 (GPIO5) |

There's an OLED on the main board. Somebody broke it (either me or itself), or
I just couldn't figure out the code, so there's no support for it.

## Coding

Copy `include/secrets.hpp.example` to `include/secrets.hpp` and update it with
your specific information: wifi details, statsd bucket information.

Then use PlatformIO to compile and upload it to your board. It will report what
it is doing over the serial interface.

## Monitoring

I set up a [Graphite](https://graphiteapp.org) database on an old laptop to
receive the data, and a [Grafana](https://grafana.com) monitoring solution to
display a pleasing graph. This is definitely overkill, but they were easy to
set up via docker.

## Acknowledgements

I went pretty far down a rabbit hole on this and can't really remember all the
spots I drew information from.

But the one I ultimately based (stole) my design from was `Top DNG`'s excellent
video on YouTube: [Making a Cheap Wi-Fi Thermometer for Home Automation](https://youtu.be/1Bsn6xnnoIs?si=6wa__fz9eMQcUE7p).

## Learnings

Next time around I would use one of the more recent chipsets from Espressif,
specifically one that is supported by their brand-spanking new Rust toolchain.
Not because there's anything wrong with the ESP8266, but because I like Rust.

Get a battery adapter, maybe? I'm not sure.

I think a couple temperature sensors: one to use for ambient room temperature,
and another that can be taped to the fermenter itself. Probably doesn't matter.

Maybe buy two sets of hardware. It costs next to nothing on AliExpress, and a
backup would have been nice. The spool of wire cost an order of magnitude more
than the hardware. Shipping and waiting is annoying. Just buy two sets at once.
