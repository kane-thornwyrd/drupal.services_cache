<?php

function services_cache_form($form_state) {
  global $site_name;
  $form = array(
    '#tree' => TRUE,
    'services_cache' => array(
    ),
  );
  ahah_helper_register($form, $form_state);


  $endpoints = services_endpoint_load_all();

  foreach ($endpoints as $name => $endpoint) {

    $form['services_cache'][$name] = array(
      '#type' => 'fieldset',
      '#title' => $endpoint->name,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['services_cache'][$name]['cache_folder'] = array(
      '#type' => 'textfield',
      '#title' => t('Directory'),
      '#description' => t('Under "%s/" ', array('%s' => file_directory_path())),
      '#default_value' => services_cache_form_values(array(
        'services_cache' => array(
          $name => array(
            'cache_folder',
          ),
        ),
        ), $form_state, $name),
    );

    $form['services_cache'][$name]['timeout'] = array(
      '#type' => 'fieldset',
      '#title' => t('Timeout'),
      '#description' => t('Just enter an amount of time.'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      'amount' => array(
        '#type' => 'textfield',
        '#default_value' => services_cache_form_values(array(
          'services_cache' => array(
            $name => array(
              'timeout' => array(
                'amount'
              ),
            ),
          ),
          ), $form_state, 7),
      ),
      'unit' => array(
        '#type' => 'select',
        '#options' => array(
          '1' => t('seconds'),
          '60' => t('minutes'),
          '3600' => t('hours'),
          '86400' => t('days'),
          '2592000' => t('~ !months (30 !days)',
            array('!months' => t('months'), '!days' => t('days'))),
          '31104000' => t('~ !years (12×30 !days)',
            array('!years' => t('years'), '!days' => t('days'))),
        ),
        '#default_value' => services_cache_form_values(array(
          'services_cache' => array(
            $name => array(
              'timeout' => array(
                'unit'
              ),
            ),
          ),
          ), $form_state, '86400'),
      ),
    );

    $form['services_cache'][$name]['secret'] = array(
      '#type' => 'textfield',
      '#title' => t('Secret'),
      '#description' => t('You have to set a secret string here, like %s if there is noone for now, to efficiently hide cache files from the smarts ones.',
        array('%s' => sha1($site_name . time() * rand(1, pi()) . 'C4nD1e5'))),
      '#default_value' => services_cache_form_values(array(
        'services_cache' => array(
          $name => array(
            'secret',
          ),
        ),
        ), $form_state),
    );


    $form['services_cache'][$name]['resources'] = array(
      '#type' => 'checkboxes',
//      '#title' => ,  $endpoint->name
      '#default_value' => services_cache_form_values(array(
        'services_cache' => array(
          $name => array(
            'resources',
          ),
        ),
        ), $form_state, array()),
      '#options' => array(),
    );

    foreach ($endpoint->resources as $resource_name => $resource) {
      $form['services_cache'][$name]['resources']['#options'][$resource_name] = $resource_name;
    }
  }

//  $form['flush'] = array(
//    '#type' => 'image_button',
//    '#src' => drupal_get_path('module', 'services_cache') . '/nuke_logo.png',
//    '#value' => t('Force Flush !'),
//    '#submit' => array('services_cache_cron'),
//  );


  return system_settings_form($form);
}
