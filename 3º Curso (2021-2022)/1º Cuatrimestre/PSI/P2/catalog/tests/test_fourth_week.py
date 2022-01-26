"""
Fourth Week Tests
Created by JAMI
EPS-UAM 2021
"""

from django.test import SimpleTestCase
import inspect


class FourthWeekTests(SimpleTestCase):

    def test_tests_models_exist(self):
        from catalog.tests.test_models import AuthorModelTest as c1
        self.assertTrue(len(str(inspect.getsourcelines(c1)))>=1000)
        self.assertIn('test_first_name_label', dir(c1))
        self.assertIn('test_date_of_death_label', dir(c1))
        self.assertIn('test_first_name_max_length', dir(c1))
        self.assertIn('test_object_name_is_last_name_comma_first_name', dir(c1))
        self.assertIn('test_get_absolute_url', dir(c1))


    def test_tests_forms_exist(self):
        from catalog.tests.test_forms import RenewBookFormTest as c2
        self.assertTrue(len(str(inspect.getsourcelines(c2)))>=1000)
        self.assertIn('test_renew_form_date_field_label', dir(c2))
        self.assertIn('test_renew_form_date_field_help_text', dir(c2))
        self.assertIn('test_renew_form_date_in_past', dir(c2))
        self.assertIn('test_renew_form_date_too_far_in_future', dir(c2))
        self.assertIn('test_renew_form_date_today', dir(c2))
        self.assertIn('test_renew_form_date_max', dir(c2))


    def test_tests_views_exist(self):
        from catalog.tests.test_views import AuthorListViewTest as c3
        self.assertTrue(len(str(inspect.getsourcelines(c3)))>=1000)
        self.assertIn('test_view_url_exists_at_desired_location', dir(c3))
        self.assertIn('test_view_url_accessible_by_name', dir(c3))
        self.assertIn('test_view_uses_correct_template', dir(c3))
        self.assertIn('test_pagination_is_ten', dir(c3))
        self.assertIn('test_lists_all_authors', dir(c3))
        from catalog.tests.test_views import LoanedBookInstancesByUserListViewTest as c4
        self.assertTrue(len(str(inspect.getsourcelines(c4)))>=1000)
        self.assertIn('test_redirect_if_not_logged_in', dir(c4))
        self.assertIn('test_logged_in_uses_correct_template', dir(c4))
        self.assertIn('test_only_borrowed_books_in_list', dir(c4))
        self.assertIn('test_pages_ordered_by_due_date', dir(c4))
        from catalog.tests.test_views import RenewBookInstancesViewTest as c5
        self.assertTrue(len(str(inspect.getsourcelines(c5)))>=1000)
        self.assertIn('test_redirect_if_not_logged_in', dir(c5))
        self.assertIn('test_forbidden_if_logged_in_but_not_correct_permission', dir(c5))
        self.assertIn('test_logged_in_with_permission_borrowed_book', dir(c5))
        self.assertIn('test_logged_in_with_permission_another_users_borrowed_book', dir(c5))
        self.assertIn('test_HTTP404_for_invalid_book_if_logged_in', dir(c5))
        self.assertIn('test_uses_correct_template', dir(c5))
        self.assertIn('test_form_renewal_date_initially_has_date_three_weeks_in_future', dir(c5))
        self.assertIn('test_redirects_to_all_borrowed_book_list_on_success', dir(c5))
        self.assertIn('test_form_invalid_renewal_date_past', dir(c5))
        self.assertIn('test_form_invalid_renewal_date_future', dir(c5))


    def test_challenge_one(self):
        from catalog.tests.test_views import AuthorCreateViewTest as c6
        self.assertTrue(len(str(inspect.getsourcelines(c6)))>=1000)
        self.assertIn('test_redirect_if_not_logged_in', dir(c6))
        self.assertIn('test_forbidden_if_logged_in_but_not_correct_permission', dir(c6))
        self.assertIn('test_logged_in_with_permission', dir(c6))
        self.assertIn('test_uses_correct_template', dir(c6))
        self.assertIn('test_form_date_of_death_initially_set_to_expected_date', dir(c6))
        self.assertIn('test_redirects_to_detail_view_on_success', dir(c6))
