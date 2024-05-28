//
// Created by ivan on 16.03.24.
//

#include <cstring>
#include "DvdReader.h"




DvdReader::DvdReader(const char *path_dvd) {
    output_fd = 0;
    finished = 0;

    printf("Opening DVD...\n");
    if (dvdnav_open(&dvdnav, path_dvd) != DVDNAV_STATUS_OK) {
        printf("Error on dvdnav_open\n");
    }
    /* set read ahead cache usage */
    if (dvdnav_set_readahead_flag(dvdnav, DVD_READ_CACHE) != DVDNAV_STATUS_OK) {
        printf("Error on dvdnav_set_readahead_flag: %s\n", dvdnav_err_to_string(dvdnav));
    }

    /* set the language */
    if (dvdnav_menu_language_select(dvdnav, DVD_LANGUAGE) != DVDNAV_STATUS_OK ||
        dvdnav_audio_language_select(dvdnav, DVD_LANGUAGE) != DVDNAV_STATUS_OK ||
        dvdnav_spu_language_select(dvdnav, DVD_LANGUAGE) != DVDNAV_STATUS_OK) {
        printf("Error on setting languages: %s\n", dvdnav_err_to_string(dvdnav));
    }

    /* set the PGC positioning flag to have position information relatively to the
     * whole feature instead of just relatively to the current chapter */
    if (dvdnav_set_PGC_positioning_flag(dvdnav, 1) != DVDNAV_STATUS_OK) {
        printf("Error on dvdnav_set_PGC_positioning_flag: %s\n", dvdnav_err_to_string(dvdnav));
    }
}


int DvdReader::writeBuffer() {
    printf("Reading...\n");


    while (!finished) {
        /* the main reading function */
        buf = mem;
#if DVD_READ_CACHE
        result = dvdnav_get_next_cache_block(dvdnav, &buf, &event, &len);
#else
        result = dvdnav_get_next_block(dvdnav, buf, &event, &len);
#endif

        if (result == DVDNAV_STATUS_ERR) {
            printf("Error getting next block: %s\n", dvdnav_err_to_string(dvdnav));
            return 3;
        }

        //printf("EVENT: %d\n", event);

        switch (event) {
            case DVDNAV_BLOCK_OK:
                /* We have received a regular block of the currently playing MPEG stream.
                 * A real player application would now pass this block through demuxing
                 * and decoding. We simply write it to disc here. */

                //make remux
                BufferReader::read_buffer(buf, sizeof(buf));
                break;
            case DVDNAV_NOP:
                /* Nothing to do here. */
                break;
            case DVDNAV_STILL_FRAME:
                /* We have reached a still frame. A real player application would wait
                 * the amount of time specified by the still's length while still handling
                 * user input to make menus and other interactive stills work.
                 * A length of 0xff means an indefinite still which has to be skipped
                 * indirectly by some user interaction. */
            {
                dvdnav_still_event_t *still_event = (dvdnav_still_event_t *) buf;
                if (still_event->length < 0xff)
                    printf("Skipping %d seconds of still frame\n", still_event->length);
                else
                    printf("Skipping indefinite length still frame\n");
                dvdnav_still_skip(dvdnav);
            }
                break;
            case DVDNAV_WAIT:
                /* We have reached a point in DVD playback, where timing is critical.
                 * Player application with internal fifos can introduce state
                 * inconsistencies, because libdvdnav is always the fifo's length
                 * ahead in the stream compared to what the application sees.
                 * Such applications should wait until their fifos are empty
                 * when they receive this type of event. */
                printf("Skipping wait condition\n");
                dvdnav_wait_skip(dvdnav);
                break;
            case DVDNAV_SPU_CLUT_CHANGE:
                /* Player applications should pass the new colour lookup table to their
                 * SPU decoder */
                break;
            case DVDNAV_SPU_STREAM_CHANGE:
                /* Player applications should inform their SPU decoder to switch channels */
                break;
            case DVDNAV_AUDIO_STREAM_CHANGE:
                /* Player applications should inform their audio decoder to switch channels */
                break;
            case DVDNAV_NAV_PACKET:
                /* A NAV packet provides PTS discontinuity information, angle linking information and
                 * button definitions for DVD menus. Angles are handled completely inside libdvdnav.
                 * For the menus to work, the NAV packet information has to be passed to the overlay
                 * engine of the player so that it knows the dimensions of the button areas. */
            {
                pci_t *pci;

                /* Applications with fifos should not use these functions to retrieve NAV packets,
                 * they should implement their own NAV handling, because the packet you get from these
                 * functions will already be ahead in the stream which can cause state inconsistencies.
                 * Applications with fifos should therefore pass the NAV packet through the fifo
                 * and decoding pipeline just like any other data. */
                pci = dvdnav_get_current_nav_pci(dvdnav);
                dvdnav_get_current_nav_dsi(dvdnav);


                if(pci->hli.hl_gi.btn_ns > 0) {
                    int button;

                    printf("Found %i DVD menu buttons...\n", pci->hli.hl_gi.btn_ns);

                    for (button = 0; button < pci->hli.hl_gi.btn_ns; button++) {
                        const btni_t *btni = &(pci->hli.btnit[button]);
                        printf("Button %i top-left @ (%i,%i), bottom-right @ (%i,%i)\n",
                               button + 1, btni->x_start, btni->y_start,
                               btni->x_end, btni->y_end);
                    }

                    button = 0;
                    while ((button <= 0) || (button > pci->hli.hl_gi.btn_ns)) {
                        //Пишем в буфер
                        printf("Which button (1 to %i): ", pci->hli.hl_gi.btn_ns);
                        scanf("%i", &button);
                    }
                    printf("Selecting button %i...\n", button);
                    /* This is the point where applications with fifos have to hand in a NAV packet
                     * which has traveled through the fifos. See the notes above. */
                    dvdnav_button_select_and_activate(dvdnav, pci, button);
                }
            }
            break;
            case DVDNAV_STOP:
            {
                close(output_fd);
                finished = 1;
            }

        };
    };
        return 0;
};



DvdReader::~DvdReader() = default;
