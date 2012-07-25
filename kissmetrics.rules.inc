<?php

/**
 * @file
 * Defines required Rules actions for KISSmetrics module.
 */

/**
 * Implements hook_rules_action_info().
 */
function kissmetrics_rules_action_info() {
  $actions = array(
    'kissmetrics_log_event' => array(
      'label' => t('Log a KISSmetrics event'),
      'group' => t('KISSmetrics'),
      'parameter' => array(
        'event' => array(
          'type' => 'text',
          'label' => t('KISSmetrics Event'),
          'required' => TRUE,
        ),
        'props' => array(
          'type' => 'text',
          'label' => t('Parameters'),
          'description' => t('Enter one parameter per line in key|value format.'),
          'required' => TRUE,
        ),
      ),
    ),
    'kissmetrics_set_property' => array(
      'label' => t('Set a property on the identified user'),
      'group' => t('KISSmetrics'),
      'parameter' => array(
        'props' => array(
          'type' => 'text',
          'label' => t('Properties'),
          'description' => t('Enter one parameter per line in key|value format.'),
          'required' => TRUE,
        ),
      ),
    ),
  );
  return $actions;
}
