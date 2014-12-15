<?php
/**
 * @file
 * API documentation for the KISSmetrics module.
 */

/**
 * Alter the KissMetrics user identifier.
 *
 * By default, this module will use the Drupal user ID (uid) once a user logs
 * in. This alter hook allows other modules to override this value. For example,
 * you could use the users email address as the identifier or any other unique
 * value on the user account.
 *
 * @param $id
 *   The currently set KISSmetrics ID. Passed by reference. If you make any
 *   changes to the $id they will be reflected in the recorded event.
 * @param $account
 *   The account object for the user whom this event is being recorded for.
 *   Provided for reference.
 */
function hook_kissmetrics_user_id_alter(&$id, $account) {
  global $user;

  if (user_is_logged_in() && !empty($user->mail)) {
    $id = $user->mail;
  }
}
