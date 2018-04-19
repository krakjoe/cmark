--TEST--
CommonMark\CQL return early
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
[link1](here1)
[link2](here2)
EOD
);

$call = new \CommonMark\CQL(<<<EOD
/children(Paragraph)[/children(Link)]
EOD
);

$call($doc, function(\CommonMark\Node $root, \CommonMark\Node $node) {
	if ($node instanceof \CommonMark\Node\Link) {
		echo "OK\n";
		return 0; /* stop */
	} else  echo "FAIL\n";
});
?>
--EXPECT--
OK
