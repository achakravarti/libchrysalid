
/* Criterion testing framework */
#include <criterion/criterion.h>


/* English sample strings */


#define SAMPLE_EN_1     "Jim quickly realized that the beautiful gowns" \
                        " are expensive."

#define SAMPLE_EN_2     "Jackie will budget for the most expensive" \
                        " zoology equipment."

/* Greek sample strings */


#define SAMPLE_EL_1     "Θέλει αρετή και τόλμη η ελευθερία. (Ανδρέας Κάλβος)."

#define SAMPLE_EL_2     "Ο καλύμνιος σφουγγαράς ψιθύρισε πως θα βουτήξει" \
                        " χωρίς να διστάζει."


// new empty string for null
// new empty string for empty
// new english panagram
// new greek panagram

Test(cy_utf8_new, null)
{
}


Test(cy_utf8_new, empty)
{
}


Test(cy_utf8_new, en)
{
}


Test(cy_utf8_new, el)
{
}


// copy empty string (single)
// copy english string (single)
// copy greek string (single)
// copy empty string (multiple)
// copy english string (multiple)
// copy greek string (multiple)


Test(cy_utf8_copy, single_empty)
{
}


Test(cy_utf8_copy, single_en)
{
}


Test(cy_utf8_copy, single_el)
{
}


Test(cy_utf8_copy, multiple_empty)
{
}


Test(cy_utf8_copy, multiple_en)
{
}


Test(cy_utf8_copy, multiple_el)
{
}



// clone empty string (single)
// clone english string (single)
// clone greek string (single)
// clone empty string (multiple)
// clone english string (multiple)
// clone greek string (multiple)


Test(cy_utf8_clone, single_empty)
{
}


Test(cy_utf8_clone, single_en)
{
}


Test(cy_utf8_clone, single_el)
{
}


Test(cy_utf8_clone, multiple_empty)
{
}


Test(cy_utf8_clone, multiple_en)
{
}


Test(cy_utf8_clone, multiple_el)
{
}


// free single empty string
// free single english string
// free single greek string

// free single copy empty string
// free single copy english string
// free single copy greek string

// free multiple copy empty string
// free multiple copy english string
// free multiple copy greek string

// free single clone empty string
// free single clone english string
// free single clone greek string

// free multiple clone empty string
// free multiple clone english string
// free multiple clone greek string


Test(cy_utf8_free, null)
{
}


Test(cy_utf8_free, single_empty)
{
}


Test(cy_utf8_free, single_en)
{
}


Test(cy_utf8_free, single_el)
{
}


Test(cy_utf8_free, single_copy_empty)
{
}


Test(cy_utf8_free, single_copy_en)
{
}


Test(cy_utf8_free, single_copy_el)
{
}


Test(cy_utf8_free, multiple_copy_empty)
{
}


Test(cy_utf8_free, multiple_copy_en)
{
}


Test(cy_utf8_free, multiple_copy_el)
{
}


Test(cy_utf8_free, single_clone_empty)
{
}


Test(cy_utf8_free, single_clone_en)
{
}


Test(cy_utf8_free, single_clone_el)
{
}


Test(cy_utf8_free, multiple_clone_empty)
{
}


Test(cy_utf8_free, multiple_clone_en)
{
}


Test(cy_utf8_free, multiple_clone_el)
{
}


// match empty string empty
// match empty string non-empty
// match english string empty
// match english string true
// match english string false
// match greek string true
// match greek string false


Test(cy_utf8_match, empty_empty)
{
}


Test(cy_utf8_match, empty_nonempty)
{
}


Test(cy_utf8_match, en_empty)
{
}


Test(cy_utf8_match, en_match)
{
}


Test(cy_utf8_match, en_nomatch)
{
}


Test(cy_utf8_match, el_match)
{
}


Test(cy_utf8_match, el_nomatch)
{
}
