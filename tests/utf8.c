
/* Libchrysalid dependencies */
#include "../include/utf8.h"

/* Criterion testing framework */
#include <criterion/criterion.h>


/* Sample strings */


/*                                                       %const:utf8:SAMPLE_EN_1
 * __NAME__
 *      {{SAMPLE_EN_1}} - English sample string #1
 *
 * __SYNOPSIS__
 *      #define SAMPLE_EN_1 "Jackie will budget for the most expensive" \
 *                          " zoology equipment."
 * __DESCRIPTION__
 *      The {{SAMPLE_EN_1}} symbolic constant represents the first sample UTF-8
 *      English (ISO 693-1 code *en*) string that is used for testing the
 *      {{cy_utf8_t}} interface. The sample string is a panagram containing all
 *      the letters of the English alphabet, and is lexicographically lower than
 *      the second English sample string {{SAMPLE_EN_2}}.
 *
 * __NOTES__
 *      We are using a panagram for {{SAMPLE_EN_1}} to maximise the number of
 *      letters in the English alphabet that we have available for testing.
 */
#define SAMPLE_EN_1     "Jackie will budget for the most expensive" \
                        " zoology equipment."


/*                                                       %const:utf8:SAMPLE_EN_2
 * __NAME__
 *      {{SAMPLE_EN_2}} - English sample string #2
 *
 * __SYNOPSIS__
 *      #define SAMPLE_EN_2 "Jim quickly realized that the beautiful gowns" \
 *                          " are expensive."
 * __DESCRIPTION__
 *      The {{SAMPLE_EN_2}} symbolic constant represents the second sample UTF-8
 *      English (ISO 693-1 code *en*) string for testing the {{cy_utf8_t}}
 *      interface. This string is a panagram just like the first sample English
 *      string {{SAMPLE_EN_1}}, but is lexicographically higher than the latter.
 *
 * __NOTES__
 *      Just as in the case of {{SAMPLE_EN_1}}, we are using a panagram for
 *      {{SAMPLE_EN_2}} to ensure that we test as many letters in the English
 *      alphabet as possible.
 */
#define SAMPLE_EN_2     "Jim quickly realized that the beautiful gowns" \
                        " are expensive."


/*                                                       %const:utf8:SAMPLE_EL_1
 * __NAME__
 *      {{SAMPLE_EL_1}} - Greek sample string #1
 *
 * __SYNOPSIS__
 *      #define SAMPLE_EL_1 "Θέλει αρετή και τόλμη η ελευθερία." \
 *                          " (Ανδρέας Κάλβος)."
 * __DESCRIPTION__
 *
 * __NOTES__
 *      The {{SAMPLE_EL_1}} string is a panagram in order to ensure that as many
 *      letters as possible of the Greek alphabet are tested. Its
 *      lexicographical order with respect to the secaond sample Greek string
 *      {{SAMPLE_EL_2}} has been determined with the Online STRING Tools web
 *      application.
 */
#define SAMPLE_EL_1     "Ζαφείρι δέξου πάγκαλο βαθῶν ψυχῆς τὸ σῆμα"



/*                                                       %const:utf8:SAMPLE_EL_2
 * __NAME__
 *      {{SAMPLE_EL_2}} - Greek sample string #2
 *
 * __SYNOPSIS__
 *      #define SAMPLE_EL_2 "Ο καλύμνιος σφουγγαράς ψιθύρισε πως θα βουτήξει" \
 *                          " χωρίς να διστάζει."
 * __DESCRIPTION__
 *      The {{SAMPLE_EL_2}} symbolic constant represents the second Greek (ISO
 *      639-1 code *el*) sample string that is used for testing the
 *      {{cy_utf8_t}} interface.
 *
 * __NOTES__
 *      The remarks for the first sample Greek string {{SAMPLE_EL_1}} are also
 *      applicable to the {{SAMPLE_EL_2}} string. {{SAMPLE_EL_2}} is set to a
 *      panagram because it maximises the number of tested letters, and its sort
 *      order compared to {{SAMPLE_EL_1}} has been checked with the Online
 *      STRING Tools web app.
 */
#define SAMPLE_EL_2     "Ο καλύμνιος σφουγγαράς ψιθύρισε πως θα βουτήξει" \
                        " χωρίς να διστάζει."


/* SAMPLE STRING LENGTHS */


/*                                                          %const:utf8:LEN_EN_1
 * __NAME__
 *      {{LEN_EN_1}} - length of {{SAMPLE_EN_1}}
 *
 * __SYNOPSIS__
 *      #define LEN_EN_1 strlen(SAMPLE_EN_1)
 *
 * __DESCRIPTION__
 */
#define LEN_EN_1    strlen(SAMPLE_EN_1)


/*                                                          %const:utf8:LEN_EN_2
 * __NAME__
 *      {{LEN_EN_2}} - length of {{SAMPLE_EN_2}}
 *
 * __SYNOPSIS__
 *      #define LEN_EN_2 strlen(SAMPLE_EN_2)
 *
 * __DESCRIPTION__
 */
#define LEN_EN_2    strlen(SAMPLE_EN_2)


/*                                                          %const:utf8:LEN_EL_1
 * __NAME__
 *      {{LEN_EL_1}} - length of {{SAMPLE_EL_1}}
 *
 * __SYNOPSIS__
 *      #define LEN_EL_1 41
 *
 * __DESCRIPTION__
 */
#define LEN_EL_1    41


/*                                                          %const:utf8:LEN_EL_2
 * __NAME__
 *      {{LEN_EL_2}} - length of {{SAMPLE_EL_2}}
 *
 * __SYNOPSIS__
 *      #define LEN_EL_2 66
 *
 * __DESCRIPTION__
 */
#define LEN_EL_2    66


/*                                                          %const:utf8:REGEX_EN
 * __NAME__
 *      {{REGEX_EN}} - regex to match English samples
 *
 * __SYNOPSIS__
 *      #define REGEX_EN "^[a-zA-Z\\s.]*$"
 *
 * __DESCRIPTION__
 */
#define REGEX_EN    "^[a-zA-Z\\s]*$"


/* Regular expression patterns */


/*                                                          %const:utf8:REGEX_EL
 * __NAME__
 *      {{REGEX_EL}} - regex to match Greek samples
 *
 * __SYNOPSIS__
 *      #define REGEX_EL "^[\\p{Greek}\\s.()]*$"
 *
 * __DESCRIPTION__
 */
#define REGEX_EL    "^[\\p{Greek}\\s.]*$"


/*                                                       %const:utf8:REGEX_EMAIL
 * __NAME__
 *      {{REGEX_EMAIL}} - regex to match email
 *
 * __SYNOPSIS__
 *      #define REGEX_EMAIL "^([a-zA-Z0-9._%-]+@[a-zA-Z0-9.-]+" \
 *                          "\\.[a-zA-Z]{2,6})*$"
 * __DESCRIPTION__
 */
#define REGEX_EMAIL     "^([a-zA-Z0-9._%-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,6})*$"


/* Tests for cy_utf8_new() */


/*                                                       %test:cy_utf8_new:empty
 * __SCENARIO__
 *      {{cy_utf8_new()}} returns a valid empty string if passed an empty
 *      {{char}} string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_new, empty)
{
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new("");

      cr_expect(s);
      cr_expect(cy_utf8_empty(s));

      cr_expect(cy_utf8_eq(s, ""));
      cr_expect(!cy_utf8_eq(s, SAMPLE_EN_1));
      cr_expect(!cy_utf8_eq(s, SAMPLE_EL_1));

      cr_expect(!cy_utf8_len(s));
      cr_expect(cy_utf8_sz(s) >= 1);

      cr_expect(cy_utf8_refc(s) == 1);

}


/*                                                          %test:cy_utf8_new:en
 * __SCENARIO__
 *      {{cy_utf8_new()}} returns a valid English string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_new, en)
{
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new(SAMPLE_EN_1);

      cr_expect(s);
      cr_expect(!cy_utf8_empty(s));

      cr_expect(cy_utf8_eq(s, SAMPLE_EN_1));
      cr_expect(!cy_utf8_eq(s, ""));
      cr_expect(!cy_utf8_eq(s, SAMPLE_EN_2));
      cr_expect(!cy_utf8_eq(s, SAMPLE_EL_1));

      cr_expect(cy_utf8_len(s) == LEN_EN_1);
      cr_expect(cy_utf8_sz(s) >= LEN_EN_1 + 1);

      cr_expect(cy_utf8_refc(s) == 1);
}


/*                                                          %test:cy_utf8_new:el
 * __SCENARIO__
 *      {{cy_utf8_new()}} returns a valid Greek string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_new, el)
{
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new(SAMPLE_EL_1);

      cr_expect(s);
      cr_expect(!cy_utf8_empty(s));

      cr_expect(cy_utf8_eq(s, SAMPLE_EL_1));
      cr_expect(!cy_utf8_eq(s, ""));
      cr_expect(!cy_utf8_eq(s, SAMPLE_EL_2));
      cr_expect(!cy_utf8_eq(s, SAMPLE_EN_1));

      cr_expect(cy_utf8_len(s) == LEN_EL_1);
      cr_expect(cy_utf8_sz(s) >= LEN_EL_1 + 1);

      cr_expect(cy_utf8_refc(s) == 1);
}


/* Tests for cy_utf8_copy() */


/*                                               %test:cy_utf8_copy:single_empty
 * __SCENARIO__
 *      {{cy_utf8_copy()}} creates a shallow copy of an empty string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_copy, single_empty)
{
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new("");
      CY_AUTO(cy_utf8_t) *s1 = cy_utf8_copy(s);

      cr_expect(s == s1);
      cr_expect(s1);
      cr_expect(cy_utf8_empty(s1));

      cr_expect(cy_utf8_eq(s1, ""));
      cr_expect(!cy_utf8_eq(s1, SAMPLE_EN_1));
      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_1));

      cr_expect(!cy_utf8_len(s1));
      cr_expect(cy_utf8_sz(s1) >= 1);

      cr_expect(cy_utf8_refc(s) == 2);
      cr_expect(cy_utf8_refc(s1) == 2);
}


/*                                                  %test:cy_utf8_copy:single_en
 * __SCENARIO__
 *      {{cy_utf8_copy()}} creates a shallow copy of an English string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_copy, single_en)
{
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new(SAMPLE_EN_1);
      CY_AUTO(cy_utf8_t) *s1 = cy_utf8_copy(s);

      cr_expect(s == s1);
      cr_expect(s1);
      cr_expect(!cy_utf8_empty(s1));

      cr_expect(cy_utf8_eq(s1, SAMPLE_EN_1));
      cr_expect(!cy_utf8_eq(s1, ""));
      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_1));

      cr_expect(cy_utf8_len(s1) == LEN_EN_1);
      cr_expect(cy_utf8_sz(s1) >= LEN_EN_1 + 1);

      cr_expect(cy_utf8_refc(s) == 2);
      cr_expect(cy_utf8_refc(s1) == 2);
}


/*                                                  %test:cy_utf8_copy:single_el
 * __SCENARIO__
 *      {{cy_utf8_copy()}} creates a shallow copy of a Greek string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_copy, single_el)
{
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new(SAMPLE_EL_1);
      CY_AUTO(cy_utf8_t) *s1 = cy_utf8_copy(s);

      cr_expect(s == s1);
      cr_expect(s1);
      cr_expect(!cy_utf8_empty(s1));

      cr_expect(cy_utf8_eq(s1, SAMPLE_EL_1));
      cr_expect(!cy_utf8_eq(s1, ""));
      cr_expect(!cy_utf8_eq(s1, SAMPLE_EN_1));

      cr_expect(cy_utf8_len(s1) == LEN_EL_1);
      cr_expect(cy_utf8_sz(s1) >= LEN_EL_1 + 1);

      cr_expect(cy_utf8_refc(s) == 2);
      cr_expect(cy_utf8_refc(s1) == 2);
}


/*                                             %test:cy_utf8_copy:multiple_empty
 * __SCENARIO__
 *      {{cy_utf8_copy()}} creates multiple shallow copies of an empty string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_copy, multiple_empty)
{
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new("");
      CY_AUTO(cy_utf8_t) *s1 = cy_utf8_copy(s);
      CY_AUTO(cy_utf8_t) *s2 = cy_utf8_copy(s);

      cr_expect(s == s1);
      cr_expect(s1 == s2);

      cr_expect(s1);
      cr_expect(s2);

      cr_expect(cy_utf8_empty(s1));
      cr_expect(cy_utf8_empty(s2));

      cr_expect(cy_utf8_eq(s1, ""));
      cr_expect(cy_utf8_eq(s2, ""));

      cr_expect(!cy_utf8_eq(s1, SAMPLE_EN_1));
      cr_expect(!cy_utf8_eq(s2, SAMPLE_EN_2));

      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_1));
      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_2));

      cr_expect(!cy_utf8_len(s1));
      cr_expect(!cy_utf8_len(s2));

      cr_expect(cy_utf8_sz(s1) >= 1);
      cr_expect(cy_utf8_sz(s2) >= 1);

      cr_expect(cy_utf8_refc(s) == 3);
      cr_expect(cy_utf8_refc(s1) == 3);
      cr_expect(cy_utf8_refc(s2) == 3);
}


/*                                                %test:cy_utf8_copy:multiple_en
 * __SCENARIO__
 *      {{cy_utf8_copy()}} creates multiple shallow copies of an English string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_copy, multiple_en)
{
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new(SAMPLE_EN_2);
      CY_AUTO(cy_utf8_t) *s1 = cy_utf8_copy(s);
      CY_AUTO(cy_utf8_t) *s2 = cy_utf8_copy(s1);

      cr_expect(s == s1);
      cr_expect(s1 == s2);

      cr_expect(s1);
      cr_expect(s2);

      cr_expect(!cy_utf8_empty(s1));
      cr_expect(!cy_utf8_empty(s2));

      cr_expect(cy_utf8_eq(s1, SAMPLE_EN_2));
      cr_expect(cy_utf8_eq(s2, SAMPLE_EN_2));

      cr_expect(!cy_utf8_eq(s1, ""));
      cr_expect(!cy_utf8_eq(s2, ""));

      cr_expect(!cy_utf8_eq(s1, SAMPLE_EN_1));
      cr_expect(!cy_utf8_eq(s2, SAMPLE_EN_1));

      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_1));
      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_1));

      cr_expect(cy_utf8_len(s1) == LEN_EN_2);
      cr_expect(cy_utf8_len(s2) == LEN_EN_2);

      cr_expect(cy_utf8_sz(s1) >= LEN_EN_2 + 1);
      cr_expect(cy_utf8_sz(s2) >= LEN_EN_2 + 1);

      cr_expect(cy_utf8_refc(s) == 3);
      cr_expect(cy_utf8_refc(s1) == 3);
      cr_expect(cy_utf8_refc(s2) == 3);
}


/*                                                %test:cy_utf8_copy:multiple_el
 * __SCENARIO__
 *      {{cy_utf8_copy()}} creates multiple shallow copies of a Greek string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_copy, multiple_el)
{
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new(SAMPLE_EL_2);
      CY_AUTO(cy_utf8_t) *s1 = cy_utf8_copy(s);
      CY_AUTO(cy_utf8_t) *s2 = cy_utf8_copy(s1);

      cr_expect(s == s1);
      cr_expect(s1 == s2);

      cr_expect(s1);
      cr_expect(s2);

      cr_expect(!cy_utf8_empty(s1));
      cr_expect(!cy_utf8_empty(s2));

      cr_expect(cy_utf8_eq(s1, SAMPLE_EL_2));
      cr_expect(cy_utf8_eq(s2, SAMPLE_EL_2));

      cr_expect(!cy_utf8_eq(s1, ""));
      cr_expect(!cy_utf8_eq(s2, ""));

      cr_expect(!cy_utf8_eq(s1, SAMPLE_EN_1));
      cr_expect(!cy_utf8_eq(s2, SAMPLE_EN_1));

      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_1));
      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_1));

      cr_expect(cy_utf8_len(s1) == LEN_EL_2);
      cr_expect(cy_utf8_len(s2) == LEN_EL_2);

      cr_expect(cy_utf8_sz(s1) >= LEN_EL_2 + 1);
      cr_expect(cy_utf8_sz(s2) >= LEN_EL_2 + 1);

      cr_expect(cy_utf8_refc(s) == 3);
      cr_expect(cy_utf8_refc(s1) == 3);
      cr_expect(cy_utf8_refc(s2) == 3);
}



/* Tests for cy_utf8_clone() */


/*                                              %test:cy_utf8_clone:single_empty
 * __SCENARIO__
 *      {{cy_utf8_clone()}} creates a deep copy of an empty string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_clone, single_empty)
{
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new("");
      CY_AUTO(cy_utf8_t) *s1 = cy_utf8_clone(s);

      cr_expect(s != s1);
      cr_expect(s1);
      cr_expect(cy_utf8_empty(s1));

      cr_expect(cy_utf8_eq(s1, ""));
      cr_expect(!cy_utf8_eq(s1, SAMPLE_EN_1));
      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_1));

      cr_expect(!cy_utf8_len(s1));
      cr_expect(cy_utf8_sz(s1) >= 1);

      cr_expect(cy_utf8_refc(s) == 1);
      cr_expect(cy_utf8_refc(s1) == 1);
}


/*                                                 %test:cy_utf8_clone:single_en
 * __SCENARIO__
 *      {{cy_utf8_clone()}} creates a deep copy of an English string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_clone, single_en)
{
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new(SAMPLE_EN_1);
      CY_AUTO(cy_utf8_t) *s1 = cy_utf8_clone(s);

      cr_expect(s != s1);
      cr_expect(s1);
      cr_expect(!cy_utf8_empty(s1));

      cr_expect(cy_utf8_eq(s1, SAMPLE_EN_1));
      cr_expect(!cy_utf8_eq(s1, ""));
      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_1));

      cr_expect(cy_utf8_len(s1) == LEN_EN_1);
      cr_expect(cy_utf8_sz(s1) >= LEN_EN_1 + 1);

      cr_expect(cy_utf8_refc(s) == 1);
      cr_expect(cy_utf8_refc(s1) == 1);
}


/*                                                 %test:cy_utf8_clone:single_el
 * __SCENARIO__
 *      {{cy_utf8_clone()}} creates a deep copy of a Greek string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_clone, single_el)
{
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new(SAMPLE_EL_1);
      CY_AUTO(cy_utf8_t) *s1 = cy_utf8_clone(s);

      cr_expect(s != s1);
      cr_expect(s1);
      cr_expect(!cy_utf8_empty(s1));

      cr_expect(cy_utf8_eq(s1, SAMPLE_EL_1));
      cr_expect(!cy_utf8_eq(s1, ""));
      cr_expect(!cy_utf8_eq(s1, SAMPLE_EN_1));

      cr_expect(cy_utf8_len(s1) == LEN_EL_1);
      cr_expect(cy_utf8_sz(s1) >= LEN_EL_1 + 1);

      cr_expect(cy_utf8_refc(s) == 1);
      cr_expect(cy_utf8_refc(s1) == 1);
}


/*                                            %test:cy_utf8_clone:multiple_empty
 * __SCENARIO__
 *      {{cy_utf8_clone()}} creates multiple deep copies of an empty string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_clone, multiple_empty)
{
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new("");
      CY_AUTO(cy_utf8_t) *s1 = cy_utf8_clone(s);
      CY_AUTO(cy_utf8_t) *s2 = cy_utf8_clone(s);

      cr_expect(s != s1);
      cr_expect(s1 != s2);

      cr_expect(s1);
      cr_expect(s2);

      cr_expect(cy_utf8_empty(s1));
      cr_expect(cy_utf8_empty(s2));

      cr_expect(cy_utf8_eq(s1, ""));
      cr_expect(cy_utf8_eq(s2, ""));

      cr_expect(!cy_utf8_eq(s1, SAMPLE_EN_1));
      cr_expect(!cy_utf8_eq(s2, SAMPLE_EN_2));

      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_1));
      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_2));

      cr_expect(!cy_utf8_len(s1));
      cr_expect(!cy_utf8_len(s2));

      cr_expect(cy_utf8_sz(s1) >= 1);
      cr_expect(cy_utf8_sz(s2) >= 1);

      cr_expect(cy_utf8_refc(s) == 1);
      cr_expect(cy_utf8_refc(s1) == 1);
      cr_expect(cy_utf8_refc(s2) == 1);
}


/*                                               %test:cy_utf8_clone:multiple_en
 * __SCENARIO__
 *      {{cy_utf8_clone()}} creates multiple deep copies of an English string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_clone, multiple_en)
{
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new(SAMPLE_EN_2);
      CY_AUTO(cy_utf8_t) *s1 = cy_utf8_clone(s);
      CY_AUTO(cy_utf8_t) *s2 = cy_utf8_clone(s1);

      cr_expect(s != s1);
      cr_expect(s1 != s2);

      cr_expect(s1);
      cr_expect(s2);

      cr_expect(!cy_utf8_empty(s1));
      cr_expect(!cy_utf8_empty(s2));

      cr_expect(cy_utf8_eq(s1, SAMPLE_EN_2));
      cr_expect(cy_utf8_eq(s2, SAMPLE_EN_2));

      cr_expect(!cy_utf8_eq(s1, ""));
      cr_expect(!cy_utf8_eq(s2, ""));

      cr_expect(!cy_utf8_eq(s1, SAMPLE_EN_1));
      cr_expect(!cy_utf8_eq(s2, SAMPLE_EN_1));

      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_1));
      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_1));

      cr_expect(cy_utf8_len(s1) == LEN_EN_2);
      cr_expect(cy_utf8_len(s2) == LEN_EN_2);

      cr_expect(cy_utf8_sz(s1) >= LEN_EN_2 + 1);
      cr_expect(cy_utf8_sz(s2) >= LEN_EN_2 + 1);

      cr_expect(cy_utf8_refc(s) == 1);
      cr_expect(cy_utf8_refc(s1) == 1);
      cr_expect(cy_utf8_refc(s2) == 1);
}


/*                                               %test:cy_utf8_clone:multiple_el
 * __SCENARIO__
 *      {{cy_utf8_clone()}} creates multiple deep copies of a Greek string
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_clone, multiple_el)
{
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new(SAMPLE_EL_2);
      CY_AUTO(cy_utf8_t) *s1 = cy_utf8_clone(s);
      CY_AUTO(cy_utf8_t) *s2 = cy_utf8_clone(s1);

      cr_expect(s != s1);
      cr_expect(s1 != s2);

      cr_expect(s1);
      cr_expect(s2);

      cr_expect(!cy_utf8_empty(s1));
      cr_expect(!cy_utf8_empty(s2));

      cr_expect(cy_utf8_eq(s1, SAMPLE_EL_2));
      cr_expect(cy_utf8_eq(s2, SAMPLE_EL_2));

      cr_expect(!cy_utf8_eq(s1, ""));
      cr_expect(!cy_utf8_eq(s2, ""));

      cr_expect(!cy_utf8_eq(s1, SAMPLE_EN_1));
      cr_expect(!cy_utf8_eq(s2, SAMPLE_EN_1));

      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_1));
      cr_expect(!cy_utf8_eq(s1, SAMPLE_EL_1));

      cr_expect(cy_utf8_len(s1) == LEN_EL_2);
      cr_expect(cy_utf8_len(s2) == LEN_EL_2);

      cr_expect(cy_utf8_sz(s1) >= LEN_EL_2 + 1);
      cr_expect(cy_utf8_sz(s2) >= LEN_EL_2 + 1);

      cr_expect(cy_utf8_refc(s) == 1);
      cr_expect(cy_utf8_refc(s1) == 1);
      cr_expect(cy_utf8_refc(s2) == 1);
}


/* Tests for cy_utf8_free() */


/*                                                       %test:cy_utf8_free:null
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on a handle to NULL
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, null)
{
      cy_utf8_t *s = NULL;
      cy_utf8_free(&s);

      cr_expect(!s);
}


/*                                               %test:cy_utf8_free:single_empty
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on a single empty string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, single_empty)
{
      cy_utf8_t *s = cy_utf8_new("");
      cy_utf8_free(&s);

      cr_expect(!s);
}


/*                                                  %test:cy_utf8_free:single_en
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on a single English string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, single_en)
{
      cy_utf8_t *s = cy_utf8_new(SAMPLE_EN_1);
      cy_utf8_free(&s);

      cr_expect(!s);
}


/*                                                  %test:cy_utf8_free:single_el
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on a single Greek string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, single_el)
{
      cy_utf8_t *s = cy_utf8_new(SAMPLE_EL_1);
      cy_utf8_free(&s);

      cr_expect(!s);
}


/*                                          %test:cy_utf8_free:single_copy_empty
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on a copy of an empty string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, single_copy_empty)
{
      cy_utf8_t *s = cy_utf8_new("");
      cy_utf8_t *s1 = cy_utf8_copy(s);
      cy_utf8_free(&s);

      cr_expect(!s);
      cr_expect(s1);
      cr_expect(cy_utf8_refc(s1) == 1);

      cy_utf8_free(&s1);
      cr_expect(!s1);
}


/*                                             %test:cy_utf8_free:single_copy_en
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on a copy of an English string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, single_copy_en)
{
      cy_utf8_t *s = cy_utf8_new(SAMPLE_EN_1);
      cy_utf8_t *s1 = cy_utf8_copy(s);
      cy_utf8_free(&s);

      cr_expect(!s);
      cr_expect(s1);
      cr_expect(cy_utf8_refc(s1) == 1);

      cy_utf8_free(&s1);
      cr_expect(!s1);
}


/*                                             %test:cy_utf8_free:single_copy_el
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on a copy of a Greek string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, single_copy_el)
{
      cy_utf8_t *s = cy_utf8_new(SAMPLE_EL_1);
      cy_utf8_t *s1 = cy_utf8_copy(s);
      cy_utf8_free(&s);

      cr_expect(!s);
      cr_expect(s1);
      cr_expect(cy_utf8_refc(s1) == 1);

      cy_utf8_free(&s1);
      cr_expect(!s1);
}


/*                                        %test:cy_utf8_free:multiple_copy_empty
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on copies of an empty string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, multiple_copy_empty)
{
      cy_utf8_t *s = cy_utf8_new("");
      cy_utf8_t *s1 = cy_utf8_copy(s);
      cy_utf8_t *s2 = cy_utf8_copy(s1);
      cy_utf8_free(&s);

      cr_expect(!s);
      cr_expect(s1);
      cr_expect(s2);
      cr_expect(cy_utf8_refc(s1) == 2);
      cr_expect(cy_utf8_refc(s2) == 2);

      cy_utf8_free(&s1);

      cr_expect(!s1);
      cr_expect(s2);
      cr_expect(cy_utf8_refc(s2) == 1);

      cy_utf8_free(&s2);
      cr_expect(!s2);
}


/*                                           %test:cy_utf8_free:multiple_copy_en
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on copies of an English string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, multiple_copy_en)
{
      cy_utf8_t *s = cy_utf8_new(SAMPLE_EN_1);
      cy_utf8_t *s1 = cy_utf8_copy(s);
      cy_utf8_t *s2 = cy_utf8_copy(s1);
      cy_utf8_free(&s);

      cr_expect(!s);
      cr_expect(s1);
      cr_expect(s2);
      cr_expect(cy_utf8_refc(s1) == 2);
      cr_expect(cy_utf8_refc(s2) == 2);

      cy_utf8_free(&s1);

      cr_expect(!s1);
      cr_expect(s2);
      cr_expect(cy_utf8_refc(s2) == 1);

      cy_utf8_free(&s2);
      cr_expect(!s2);
}


/*                                           %test:cy_utf8_free:multiple_copy_el
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on copies of a Greek string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, multiple_copy_el)
{
      cy_utf8_t *s = cy_utf8_new(SAMPLE_EL_1);
      cy_utf8_t *s1 = cy_utf8_copy(s);
      cy_utf8_t *s2 = cy_utf8_copy(s1);
      cy_utf8_free(&s);

      cr_expect(!s);
      cr_expect(s1);
      cr_expect(s2);
      cr_expect(cy_utf8_refc(s1) == 2);
      cr_expect(cy_utf8_refc(s2) == 2);

      cy_utf8_free(&s1);

      cr_expect(!s1);
      cr_expect(s2);
      cr_expect(cy_utf8_refc(s2) == 1);

      cy_utf8_free(&s2);
      cr_expect(!s2);
}


/*                                         %test:cy_utf8_free:single_clone_empty
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on a clone of an empty string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, single_clone_empty)
{
      cy_utf8_t *s = cy_utf8_new("");
      cy_utf8_t *s1 = cy_utf8_clone(s);
      cy_utf8_free(&s);

      cr_expect(!s);
      cr_expect(s1);
      cr_expect(cy_utf8_refc(s1) == 1);

      cy_utf8_free(&s1);
      cr_expect(!s1);
}


/*                                            %test:cy_utf8_free:single_clone_en
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on a clone of an English string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, single_clone_en)
{
      cy_utf8_t *s = cy_utf8_new(SAMPLE_EN_2);
      cy_utf8_t *s1 = cy_utf8_clone(s);
      cy_utf8_free(&s);

      cr_expect(!s);
      cr_expect(s1);
      cr_expect(cy_utf8_refc(s1) == 1);

      cy_utf8_free(&s1);
      cr_expect(!s1);
}


/*                                            %test:cy_utf8_free:single_clone_el
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on a clone of a Greek string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, single_clone_el)
{
      cy_utf8_t *s = cy_utf8_new(SAMPLE_EL_2);
      cy_utf8_t *s1 = cy_utf8_clone(s);
      cy_utf8_free(&s);

      cr_expect(!s);
      cr_expect(s1);
      cr_expect(cy_utf8_refc(s1) == 1);

      cy_utf8_free(&s1);
      cr_expect(!s1);
}


/*                                         %test:cy_utf8_free:single_clone_empty
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on clones of an empty string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, multiple_clone_empty)
{
      cy_utf8_t *s = cy_utf8_new("");
      cy_utf8_t *s1 = cy_utf8_clone(s);
      cy_utf8_t *s2 = cy_utf8_clone(s1);
      cy_utf8_free(&s);

      cr_expect(!s);
      cr_expect(s1);
      cr_expect(s2);
      cr_expect(cy_utf8_refc(s1) == 1);
      cr_expect(cy_utf8_refc(s2) == 1);

      cy_utf8_free(&s1);

      cr_expect(!s1);
      cr_expect(s2);
      cr_expect(cy_utf8_refc(s2) == 1);

      cy_utf8_free(&s2);
      cr_expect(!s2);
}


/*                                          %test:cy_utf8_free:multiple_clone_en
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on clones of an English string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, multiple_clone_en)
{
      cy_utf8_t *s = cy_utf8_new(SAMPLE_EN_1);
      cy_utf8_t *s1 = cy_utf8_clone(s);
      cy_utf8_t *s2 = cy_utf8_clone(s1);
      cy_utf8_free(&s);

      cr_expect(!s);
      cr_expect(s1);
      cr_expect(s2);
      cr_expect(cy_utf8_refc(s1) == 1);
      cr_expect(cy_utf8_refc(s2) == 1);

      cy_utf8_free(&s1);

      cr_expect(!s1);
      cr_expect(s2);
      cr_expect(cy_utf8_refc(s2) == 1);

      cy_utf8_free(&s2);
      cr_expect(!s2);
}


/*                                          %test:cy_utf8_free:multiple_clone_el
 * __SCENARIO__
 *      {{cy_utf8_free()}} is called on clones of a Greek string instance
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_free, multiple_clone_el)
{
      cy_utf8_t *s = cy_utf8_new(SAMPLE_EL_1);
      cy_utf8_t *s1 = cy_utf8_clone(s);
      cy_utf8_t *s2 = cy_utf8_clone(s1);
      cy_utf8_free(&s);

      cr_expect(!s);
      cr_expect(s1);
      cr_expect(s2);
      cr_expect(cy_utf8_refc(s1) == 1);
      cr_expect(cy_utf8_refc(s2) == 1);

      cy_utf8_free(&s1);

      cr_expect(!s1);
      cr_expect(s2);
      cr_expect(cy_utf8_refc(s2) == 1);

      cy_utf8_free(&s2);
      cr_expect(!s2);
}


/* Tests for cy_utf8_match() */


/*                                               %test:cy_utf8_match:empty_empty
 * __SCENARIO__
 *      {{cy_utf8_match()}} called on empty string with empty pattern
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_match, empty_empty)
{
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new("");
      bool m = cy_utf8_match(s, "");

      cr_assert(!m);
}


/*                                            %test:cy_utf8_match:empty_nonempty
 * __SCENARIO__
 *      {{cy_utf8_match()}} called on empty string with valid pattern
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_match, empty_nonempty)
{
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new("");
      bool m = cy_utf8_match(s, REGEX_EMAIL);

      cr_assert(!m);
}


/*                                                  %test:cy_utf8_match:en_empty
 * __SCENARIO__
 *      {{cy_utf8_match()}} called on English string with empty pattern
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_match, en_empty)
{
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new(SAMPLE_EN_1);
      bool m = cy_utf8_match(s, "");

      cr_assert(!m);
}


/*                                                  %test:cy_utf8_match:en_match
 * __SCENARIO__
 *      {{cy_utf8_match()}} called on English string with matching pattern
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_match, en_match)
{
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new(SAMPLE_EN_1);
      bool m = cy_utf8_match(s, REGEX_EN);

      cr_assert(m);
}


/*                                                %test:cy_utf8_match:en_nomatch
 * __SCENARIO__
 *      {{cy_utf8_match()}} called on English string with non-matching pattern
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_match, en_nomatch)
{
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new(SAMPLE_EN_1);
      bool m = cy_utf8_match(s, REGEX_EMAIL);

      cr_assert(!m);
}


/*                                                  %test:cy_utf8_match:el_empty
 * __SCENARIO__
 *      {{cy_utf8_match()}} called on Greek string with empty pattern
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_match, el_empty)
{
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new(SAMPLE_EL_1);
      bool m = cy_utf8_match(s, "");

      cr_assert(!m);
}


/*                                                  %test:cy_utf8_match:el_match
 * __SCENARIO__
 *      {{cy_utf8_match()}} called on Greek string with matching pattern
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_match, el_match)
{
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new(SAMPLE_EL_1);
      bool m = cy_utf8_match(s, REGEX_EL);

      cr_assert(m);
}


/*                                                %test:cy_utf8_match:el_nomatch
 * __SCENARIO__
 *      {{cy_utf8_match()}} called on Greek string with non-matching pattern
 *
 * __GIVEN__
 *
 * __WHEN__
 *
 * __THEN__
 */
Test(cy_utf8_match, el_nomatch)
{
      CY_AUTO(cy_utf8_t) *s = cy_utf8_new(SAMPLE_EL_1);
      bool m = cy_utf8_match(s, REGEX_EMAIL);

      cr_assert(!m);
}
