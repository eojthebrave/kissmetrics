<?php

/**
 * @file
 * Contains KISSmetrics administration form callbacks.
 */

/**
 * Configuration form callback.
 */
function kissmetrics_configuration_form($form, &$form_state) {
  $form = array();

  $form['api_information'] = array(
    '#type' => 'fieldset',
    '#title' => t('API Information'),
  );
  $form['api_information']['kissmetrics_api_key'] = array(
    '#title' => t('API Key'),
    '#type' => 'textfield',
    '#default_value' => variable_get('kissmetrics_api_key'),
    '#required' => TRUE,
  );
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
  );
  $form['settings']['kissmetrics_use_cron'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Cron'),
    '#description' => t('Use Cron for sending data to KISSmetrics. Highly recommended.'),
    '#default_value' => variable_get('kissmetrics_use_cron', TRUE),
  );
  if (!kissmetrics_check_directory()) {
    form_set_error('kissmetrics_log_dir', t('The directory %directory does not exist or is not writable.', array('%directory' => kissmetrics_get_directory())));
  }
  $form['settings']['kissmetrics_log_dir'] = array(
    '#type' => 'textfield',
    '#title' => t('Request log directory'),
    '#default_value' => variable_get('kissmetrics_log_dir', 'kissmetrics'),
    '#size' => 30,
    '#maxlength' => 255,
    '#description' => t('Subdirectory where the request log data will be stored. This folder <strong>must not be shared</strong> with any other Drupal site or install using KISSmetrics.'),
    '#field_prefix' => file_build_uri(''),
    '#states' => array(
      'visible' => array(
        ':input[name="kissmetrics_use_cron"]' => array('checked' => TRUE),
      ),
      'required' => array(
        ':input[name="kissmetrics_use_cron"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['settings']['pages'] = array(
    '#type' => 'fieldset',
    '#title' => t('Pages'),
    '#description' => t('Specify the pages that KISSmetrics is enabled/disabled on them'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $description = t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>'));
  $form['settings']['pages']['kissmetrics_visibility_mode'] = array(
    '#type' => 'radios',
    '#title' => t('Add tracking to specific pages'),
    '#options' => array(
      t('Every page except the listed pages'),
      t('The listed pages only'),
    ),
    '#default_value' => variable_get('kissmetrics_visibility_mode', 0),
  );
  $form['settings']['pages']['kissmetrics_visibility_pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Pages'),
    '#description' => $description,
    '#default_value' => variable_get('kissmetrics_visibility_pages', KISSMETRICS_PAGES),
  );

  $form['#submit'][] = 'kissmetrics_configuration_form_submit';

  return system_settings_form($form);
}

/**
 * Configuration form validate callback.
 */
function kissmetrics_configuration_form_validate($form, &$form_state) {
  $form_state['values']['kissmetrics_visibility_pages'] = trim($form_state['values']['kissmetrics_visibility_pages']);

  // Require a directory for the request log if cron log processing is enabled.
  if ($form_state['values']['kissmetrics_use_cron']) {
    $log_dir = trim($form_state['values']['kissmetrics_log_dir']);

    if (empty($log_dir)) {
      form_set_error('kissmetrics_log_dir', t('Request log directory field is required.'));
    }
  }
}

/**
 * Configuration form submit callback.
 */
function kissmetrics_configuration_form_submit($form, &$form_state) {
  $old_dir = kissmetrics_get_directory();
  $new_dir = kissmetrics_get_directory($form_state['values']['kissmetrics_log_dir']);

  // Move the request log if the directory changed.
  if ($old_dir != $new_dir) {
    kissmetrics_directory_move($old_dir, $new_dir);
  }
}
