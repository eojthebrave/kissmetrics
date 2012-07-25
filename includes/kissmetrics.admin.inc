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
  $form['api_information']['api_key'] = array(
    '#title' => t('API Key'),
    '#type' => 'textfield',
    '#default_value' => variable_get('kissmetrics_api_key'),
    '#required' => TRUE,
  );
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
  );
  $form['settings']['use_cron'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Cron'),
    '#description' => t('Use Cron for sending data to KISSmetrics. Highly recommended.'),
    '#default_value' => variable_get('kissmetrics_use_cron', TRUE),
  );
  $form['settings']['log_dir'] = array(
    '#type' => 'textfield',
    '#title' => t('Log directory'),
    '#default_value' => variable_get('kissmetrics_log_dir', '/tmp'),
  );
  $form['settings']['pages'] = array(
    '#type' => 'fieldset',
    '#title' => t('Pages'),
    '#description' => t('Specify the pages that KISSmetrics is enabled/disabled on them'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $description = t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>'));
  $form['settings']['pages']['visibility_mode'] = array(
    '#type' => 'radios',
    '#title' => t('Add tracking to specific pages'),
    '#options' => array(
      t('Every page except the listed pages'),
      t('The listed pages only'),
    ),
    '#default_value' => variable_get('kissmetrics_visibility_mode', 0),
  );
  $form['settings']['pages']['kissmetrics_pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Pages'),
    '#description' => $description,
    '#default_value' => variable_get('kissmetrics_visibility_pages', KISSMETRICS_PAGES),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

function kissmetrics_configuration_form_validate($form, &$form_state) {
  $form_state['values']['kissmetrics_pages'] = trim($form_state['values']['kissmetrics_pages']);
  if (!file_exists($form_state['values']['log_dir'])) {
    form_set_error('log_dir', t('The specified directory does not exist.'));
  }
  if (!is_writeable($form_state['values']['log_dir'])) {
    form_set_error('log_dir', t('The specified directory is not writable.'));
  }
}

function kissmetrics_configuration_form_submit($form, &$form_state) {
  variable_set('kissmetrics_api_key', $form_state['values']['api_key']);
  variable_set('kissmetrics_visibility_pages', $form_state['values']['kissmetrics_pages']);
  variable_set('kissmetrics_use_cron', $form_state['values']['use_cron']);
  variable_set('kissmetrics_visibility_mode', $form_state['values']['visibility_mode']);
  variable_set('kissmetrics_log_dir', $form_state['values']['log_dir']);
}
